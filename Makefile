PYTHON ?= python3

.PHONY: nightly install check-python

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
	@command python -m pip install -r requirements.txt

nightly: check-python
	bash infra/nightly.sh reports/
