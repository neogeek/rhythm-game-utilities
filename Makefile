help:
	@fgrep -h "##" $(MAKEFILE_LIST) | sed -e 's/##//' | tail -n +2

build:
	./bin/build.sh

debug: build ## Build debug
	dotnet build RhythmGameUtilities/*.csproj --configuration Debug

release: build ## Build release
	dotnet build RhythmGameUtilities/*.csproj --configuration Release

test: build ## Run tests
	dotnet test RhythmGameUtilities.Tests/*.csproj

copy: ## Copy files from project to UnityPackage
	rsync -avm --exclude='obj/' --exclude='bin/' --include='*.cs' --include='*/' --exclude='*' ./RhythmGameUtilities/ ./UnityPackage/
	cp LICENSE ./UnityPackage/
	cp README.md ./UnityPackage/
	cp screenshot.png ./UnityPackage/
	rsync -avm --exclude='obj/' --exclude='bin/' --include='*.cs' --include='*/' --exclude='*' ./RhythmGameUtilities.Tests/ ./UnityPackage/Editor/Tests

rcopy: ## Copy files from UnityPackage back to project
	rsync -avm --exclude='Editor/' --include='*.cs' --include='*/' --exclude='*' ./UnityPackage/ ./RhythmGameUtilities

clean: ## Clean project
	git clean -xdf

.PHONY: build
