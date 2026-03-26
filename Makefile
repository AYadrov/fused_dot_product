PYTHON ?= python3
VENV_DIR ?= .venv
VENV_PYTHON := $(VENV_DIR)/bin/python3
REPORTS_DIR ?= reports
NIGHTLY_NUM_POINTS ?= 1000
UNITTESTS_NUM_POINTS ?= 100
SEED ?= $(shell date "+%Y%j")

.PHONY: nightly install check-python unit-tests venv

check-python:
	@echo "Checking Python installation"
	@command -v $(PYTHON) >/dev/null 2>&1 || { \
		echo "$(PYTHON) not found. Please install Python 3.11+."; \
		exit 1; \
	}
	@echo "Python found: $$($(PYTHON) --version)"
	@$(PYTHON) -m pip --version >/dev/null 2>&1 || { \
		echo "pip not found for $(PYTHON). Please install pip."; \
		exit 1; \
	}

venv: check-python
	@echo "Ensuring virtual environment exists in $(VENV_DIR)"
	@if [ ! -x "$(VENV_PYTHON)" ]; then \
		$(PYTHON) -m venv $(VENV_DIR); \
	fi

install: venv
	@echo "Installing dependencies into $(VENV_DIR)"
	@$(VENV_PYTHON) -m pip install --upgrade -r requirements.txt

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
