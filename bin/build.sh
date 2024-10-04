#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
GREENON=$(tput setaf 2)
COLOROFF=$(tput sgr0)

(

    mkdir -p build/

    cd "${SCRIPT_DIR}" || exit

    cd ..

    printf "Building macOS libraries ... "

    g++ -std=c++17 -shared -fPIC -arch arm64 -o build/libRhythmGameUtilities-arm64.dylib include/RhythmGameUtilities/RhythmGameUtilities.cpp
    g++ -std=c++17 -shared -fPIC -arch x86_64 -o build/libRhythmGameUtilities-x86_64.dylib include/RhythmGameUtilities/RhythmGameUtilities.cpp

    if [[ ! -f build/libRhythmGameUtilities-arm64.dylib || ! -f build/libRhythmGameUtilities-x86_64.dylib ]]; then
        exit 1
    fi

    lipo -create -output build/libRhythmGameUtilities.dylib build/libRhythmGameUtilities-arm64.dylib build/libRhythmGameUtilities-x86_64.dylib

    lipo -info build/libRhythmGameUtilities.dylib

    mkdir -p UnityPackage/Libs/macOS
    mkdir -p RhythmGameUtilities/Libs/macOS

    cp build/libRhythmGameUtilities.dylib UnityPackage/Libs/macOS
    cp build/libRhythmGameUtilities.dylib RhythmGameUtilities/Libs/macOS

    printf "%sDONE%s\n" "${GREENON}" "${COLOROFF}"

)
