help:
	@fgrep -h "##" $(MAKEFILE_LIST) | sed -e 's/##//' | tail -n +2

build: ## Build libraries
	./bin/build.sh

debug: build ## Build debug
	dotnet build RhythmGameUtilities/*.csproj --configuration Debug

release: build ## Build release
	dotnet build RhythmGameUtilities/*.csproj --configuration Release

test: build ## Run tests
	./bin/test.sh
	dotnet test RhythmGameUtilities.Tests/*.csproj

copy: ## Copy files from project to UnityPackage
	./bin/copy.sh

rcopy: ## Copy files from UnityPackage back to project
	./bin/rcopy.sh

clean: ## Clean project
	git clean -xdf

tidy:
	clang-tidy include/**/*.hpp -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*

.PHONY: build
