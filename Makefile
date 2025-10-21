tests: basic-tests

basic-tests:
	@echo "Running utils/basics.py..."
	@cd .. && python -m fused_dot_product.utils.basics
	@echo "Complete"
