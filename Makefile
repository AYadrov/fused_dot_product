check-python:
	@echo "Checking Python installation"
	@command -v python3 >/dev/null 2>&1 || { \
		echo "Python3 not found. Please install Python 3.8+."; \
		exit 1; \
	}
	@echo "Python found: $$(python3 --version)"
	
install:
	@echo "Installing dependencies"
	@command python -m pip install -r requirements.txt

unit-tests:
	@echo "Running infra/unittests.py..."
	@cd .. && python -m unittest -v fused_dot_product.infra.unittests
	@echo "Complete"
