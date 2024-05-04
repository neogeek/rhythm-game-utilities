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
	(cd RhythmGameUtilities && find . -type f -name "*.cs" -not -path '*/obj/*' -not -path '*/bin/*' -exec cp {} ../UnityPackage/{} \;)
	(cd RhythmGameUtilities.Tests && find . -type f -name "*.cs" -not -path '*/obj/*' -not -path '*/bin/*' -exec cp {} ../UnityPackage/Editor/Tests/{} \;)
	cp LICENSE ./UnityPackage/
	cp README.md ./UnityPackage/
	cp screenshot.png ./UnityPackage/

rcopy: ## Copy files from UnityPackage back to project
	(cd UnityPackage && find . -type f -name "*.cs" -not -path '*/Editor/*' -exec cp {} ../RhythmGameUtilities/{} \;)

clean: ## Clean project
	git clean -xdf

.PHONY: build
