PYTHON ?= python3

.PHONY: nightly install check-python unit-tests

check-python:
	@echo "Checking Python installation"
	@command -v $(PYTHON) >/dev/null 2>&1 || { \
		echo "$(PYTHON) not found. Please install Python 3.8+."; \
		exit 1; \
	}
	@echo "Python found: $$($(PYTHON) --version)"
	@$(PYTHON) -m pip --version >/dev/null 2>&1 || { \
		echo "pip not found for $(PYTHON). Please install pip."; \
		exit 1; \
	}

install: check-python
	@echo "Installing dependencies"
	@$(PYTHON) -m pip install --upgrade pip
	@$(PYTHON) -m pip install -r requirements.txt

unit-tests: install
	@echo "Running infra/unittests.py..."
	@cd .. && $(PYTHON) -m fused_dot_product.infra.unittests --seed 0 --num-points 100
	@echo "Complete"

nightly: check-python
	bash infra/nightly.sh reports/
