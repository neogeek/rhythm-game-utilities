help:
	@fgrep -h "##" $(MAKEFILE_LIST) | sed -e 's/##//' | tail -n +2

build: ## Build Lua plugin
	./build.sh

test: build ## Test Lua plugin
	lua test.lua

install-dependencies: ## Install Dependencies
	brew install lua
