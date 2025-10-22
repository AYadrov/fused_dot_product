check-python:
	@echo "Checking Python installation"
	@command -v python3 >/dev/null 2>&1 || { \
		echo "Python3 not found. Please install Python 3.8+."; \
		exit 1; \
	}
	@echo "Python found: $$(python3 --version)"

install: check-python
	@echo "Installing fixedpoint package"
	@pip install -U fixedpoint
	@echo "Installation is done"

tests: basic-tests conventional-tests

basic-tests:
	@echo "Running utils/basics.py..."
	@cd .. && python -m fused_dot_product.utils.basics
	@echo "Complete"

conventional-tests:
	@echo "Running designs/conventional.py..."
	@cd .. && python -m fused_dot_product.designs.conventional
	@echo "Complete"

