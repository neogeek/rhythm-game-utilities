#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
GREENON=$(tput setaf 2)
COLOROFF=$(tput sgr0)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    (
        cd RhythmGameUtilities/

        find . -type f -name "*.cs" -not -path '*/obj/*' -not -path '*/bin/*' | while read -r FILE; do
            DIRECTORY=$(dirname "${FILE}")

            mkdir -p "../UnityPackage/${DIRECTORY}"

            cp -R "${FILE}" "../UnityPackage/${FILE}"
        done
    )

    (
        cd RhythmGameUtilities.Tests/

        find . -type f -name "*.cs" -not -path '*/obj/*' -not -path '*/bin/*' | while read -r FILE; do
            DIRECTORY=$(dirname "${FILE}")

            mkdir -p "../UnityPackage/Editor/Tests/${DIRECTORY}"

            cp -R "${FILE}" "../UnityPackage/Editor/Tests/${FILE}"
        done
    )

	cp LICENSE ./UnityPackage/
	cp README.md ./RhythmGameUtilities/
	cp README.md ./UnityPackage/
	cp screenshot.png ./UnityPackage/

)
