PYTHON ?= $(shell \
	if command -v python3.11 >/dev/null 2>&1; then printf '%s' python3.11; \
	elif command -v python3.10 >/dev/null 2>&1; then printf '%s' python3.10; \
	else printf '%s' python3; \
	fi)
VENV_DIR ?= .venv
VENV_PYTHON := $(VENV_DIR)/bin/python3
VENV_PIP := $(VENV_PYTHON) -m pip
REPORTS_DIR ?= reports
NIGHTLY_NUM_POINTS ?= 1000
UNITTESTS_NUM_POINTS ?= 100
SEED ?= $(shell date "+%Y%j")
DREAL_REPO ?= https://github.com/dreal/dreal4

.PHONY: nightly install check-python unit-tests venv install-prereqs install-python-deps install-dreal-python

check-python:
	@echo "Checking Python installation"
	@command -v $(PYTHON) >/dev/null 2>&1 || { \
		echo "$(PYTHON) not found. Please install Python 3.10 or 3.11."; \
		exit 1; \
	}
	@echo "Python found: $$($(PYTHON) --version)"
	@$(PYTHON) -c 'import sys; raise SystemExit(0 if sys.version_info[:2] in {(3, 10), (3, 11)} else 1)' || { \
		echo "$(PYTHON) must be Python 3.10 or 3.11 for dReal compatibility."; \
		exit 1; \
	}
	@$(PYTHON) -m pip --version >/dev/null 2>&1 || { \
		echo "pip not found for $(PYTHON). Please install pip."; \
		exit 1; \
	}

venv: check-python
	@echo "Ensuring virtual environment exists in $(VENV_DIR)"
	@if [ ! -x "$(VENV_PYTHON)" ]; then \
		$(PYTHON) -m venv $(VENV_DIR); \
	elif [ "$$($(VENV_PYTHON) -c 'import sys; print(f"{sys.version_info.major}.{sys.version_info.minor}")')" != "$$($(PYTHON) -c 'import sys; print(f"{sys.version_info.major}.{sys.version_info.minor}")')" ]; then \
		echo "Recreating $(VENV_DIR) with $(PYTHON)"; \
		$(PYTHON) -m venv --clear $(VENV_DIR); \
	fi

install-prereqs:
	@echo "Installing dReal prerequisites"
	@command -v git >/dev/null 2>&1 || { \
		echo "git not found. Please install git."; \
		exit 1; \
	}
	@set -e; \
	tmp_dir="$$(mktemp -d /tmp/dreal4-prereqs.XXXXXX)"; \
	trap 'rm -rf "$$tmp_dir"' EXIT; \
	echo "Cloning dReal setup repo into $$tmp_dir"; \
	git clone --depth 1 "$(DREAL_REPO)" "$$tmp_dir/dreal4"; \
	cd "$$tmp_dir/dreal4"; \
	uname_s="$$(uname -s)"; \
	if [ "$$uname_s" = "Darwin" ]; then \
		bash ./setup/mac/install_prereqs.sh; \
	elif [ "$$uname_s" = "Linux" ]; then \
		if command -v lsb_release >/dev/null 2>&1; then \
			ubuntu_version="$$(lsb_release -r -s)"; \
		elif [ -r /etc/os-release ]; then \
			. /etc/os-release; \
			ubuntu_version="$$VERSION_ID"; \
		else \
			echo "Cannot detect Ubuntu version"; \
			exit 1; \
		fi; \
		case "$$ubuntu_version" in \
			24.04) \
				sed 's/\<python3-distutils\>//g' ./setup/ubuntu/22.04/install_prereqs.sh > "$$tmp_dir/install_prereqs_24.04.sh"; \
				chmod +x "$$tmp_dir/install_prereqs_24.04.sh"; \
				sudo "$$tmp_dir/install_prereqs_24.04.sh" ;; \
			22.04|20.04) sudo ./setup/ubuntu/$$ubuntu_version/install_prereqs.sh ;; \
			*) echo "Unsupported Ubuntu version: $$ubuntu_version"; exit 1 ;; \
		esac; \
	else \
		echo "Unsupported OS: $$uname_s"; \
		exit 1; \
	fi

install-python-deps: venv
	@echo "Installing Python dependencies into $(VENV_DIR)"
	@$(VENV_PIP) install --upgrade pip setuptools
	@$(VENV_PIP) install --upgrade -r requirements.txt

install-dreal-python: venv
	@echo "Installing dReal Python bindings into $(VENV_DIR)"
	@$(VENV_PIP) install --upgrade "wheel<0.38"
	@$(VENV_PIP) install --no-build-isolation dreal

install: install-prereqs install-python-deps install-dreal-python

unit-tests: install
	@echo "Running infra/unittests.py..."
	@$(VENV_PYTHON) -m infra.unittests --seed 0 --num-points "$(UNITTESTS_NUM_POINTS)"
	@echo "Complete"

nightly: install
	@echo "Running infra/nightly.sh with seed $(SEED)..."
	@PYTHON=$(VENV_PYTHON) \
		bash infra/nightly.sh --report-dir "$(REPORTS_DIR)" --seed "$(SEED)" --num-points "$(NIGHTLY_NUM_POINTS)"
	@echo "Generating $(REPORTS_DIR)/index.html from report.json..."
	@$(VENV_PYTHON) -m infra.make_html --report-dir "$(REPORTS_DIR)"
	@echo "Complete"
