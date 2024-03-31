#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    mkdir -p build/

    cd "${SCRIPT_DIR}" || exit

    cd ..

    g++ -std=c++17 -shared -fPIC -o build/libRhythmGameUtilities.dylib includes/RhythmGameUtilities/RhythmGameUtilities.cpp

    mkdir -p UnityPackage/Libs/macOS
    mkdir -p RhythmGameUtilities/Libs/macOS

    cp build/libRhythmGameUtilities.dylib UnityPackage/Libs/macOS
    cp build/libRhythmGameUtilities.dylib RhythmGameUtilities/Libs/macOS

)
