PYTHON ?= python
VENV_DIR ?= .venv
VENV_PYTHON := $(VENV_DIR)/bin/python
REQUIREMENTS_STAMP := $(VENV_DIR)/.requirements.stamp
REPORTS_DIR ?= reports

.PHONY: nightly install check-python unit-tests

check-python:
	@echo "Checking Python installation"
	@command -v $(PYTHON) >/dev/null 2>&1 || { \
		echo "$(PYTHON) not found. Please install Python 3.11."; \
		exit 1; \
	}
	@echo "Python found: $$($(PYTHON) --version)"
	@$(PYTHON) -m pip --version >/dev/null 2>&1 || { \
		echo "pip not found for $(PYTHON). Please install pip."; \
		exit 1; \
	}

$(VENV_PYTHON):
	@echo "Creating virtual environment in $(VENV_DIR)"
	@$(PYTHON) -m venv $(VENV_DIR)

$(REQUIREMENTS_STAMP): requirements.txt | $(VENV_PYTHON)
	@echo "Installing dependencies into $(VENV_DIR)"
	@$(VENV_PYTHON) -m pip install --upgrade pip
	@$(VENV_PYTHON) -m pip install -r requirements.txt
	@touch $(REQUIREMENTS_STAMP)

install: check-python $(REQUIREMENTS_STAMP)

unit-tests: install
	@echo "Running infra/unittests.py..."
	@$(VENV_PYTHON) -m infra.unittests --seed 0 --num-points 100
	@echo "Complete"

nightly: install
	@PYTHON=$(VENV_PYTHON) bash infra/nightly.sh $(REPORTS_DIR)/
