import shutil
import tempfile
import unittest
import ctypes
import subprocess
from pathlib import Path

from fused_dot_product import Node, StaticType, TupleT


def _find_cpp_compiler() -> str | None:
    for candidate in ("c++", "g++", "clang++"):
        compiler = shutil.which(candidate)
        if compiler is not None:
            return compiler
    raise unittest.SkipTest("A C++ compiler is required for lowering round-trip tests")


def _abi_bits(type_: StaticType) -> int:
    if isinstance(type_, TupleT):
        raise TypeError("jit_compile supports only scalar arguments and return types")

    total_bits = type_.total_bits()
    if total_bits <= 8:
        return 8
    if total_bits <= 16:
        return 16
    if total_bits <= 32:
        return 32
    if total_bits <= 64:
        return 64
    raise TypeError("jit_compile supports only values up to 64 bits")


def _cpp_abi_type(type_: StaticType) -> str:
    return f"std::uint{_abi_bits(type_)}_t"


def _ctypes_abi_type(type_: StaticType):
    bits = _abi_bits(type_)
    if bits == 8:
        return ctypes.c_uint8
    if bits == 16:
        return ctypes.c_uint16
    if bits == 32:
        return ctypes.c_uint32
    return ctypes.c_uint64


def jit_compile(node: Node):
    if not hasattr(node, "inner_args"):
        raise TypeError("jit_compile expects a Primitive or Composite node")

    function_name = "jit_entry"
    source = node.to_cpp(function_name)
    compiler = _find_cpp_compiler()

    tempdir = tempfile.TemporaryDirectory()
    temp_path = Path(tempdir.name)
    header_path = temp_path / "lowered.hpp"
    wrapper_path = temp_path / "wrapper.cpp"
    library_path = temp_path / "lowered.so"

    header_path.write_text(source, encoding="utf-8")
    arg_decls = [
        f"{_cpp_abi_type(arg.node_type)} arg_{idx}"
        for idx, arg in enumerate(node.inner_args)
    ]
    call_args = ", ".join(f"arg_{idx}" for idx, _ in enumerate(node.inner_args))
    return_type = _cpp_abi_type(node.node_type)

    wrapper_path.write_text(
        "\n".join(
            [
                "#include <cstdint>",
                '#include "lowered.hpp"',
                "",
                f'extern "C" {return_type} {function_name}_entry({", ".join(arg_decls)}) {{',
                f"    return static_cast<{return_type}>({function_name}({call_args}));",
                "}",
                "",
            ]
        ),
        encoding="utf-8",
    )

    command = [
        compiler,
        "-std=c++17",
        "-shared",
        "-fPIC",
        str(wrapper_path),
        "-o",
        str(library_path),
    ]
    result = subprocess.run(command, capture_output=True, text=True, check=False)
    if result.returncode != 0:
        tempdir.cleanup()
        raise AssertionError(
            "Failed to compile lowered C++:\n"
            f"stdout:\n{result.stdout}\n"
            f"stderr:\n{result.stderr}"
        )

    library = ctypes.CDLL(str(library_path))
    func = getattr(library, f"{function_name}_entry")
    func.argtypes = [_ctypes_abi_type(arg.node_type) for arg in node.inner_args]
    func.restype = _ctypes_abi_type(node.node_type)
    return tempdir, func

