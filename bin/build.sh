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

    g++ -std=c++17 -shared -fPIC -o build/libRhythmGameUtilities.dylib includes/RhythmGameUtilities/RhythmGameUtilities.cpp

    mkdir -p UnityPackage/Libs/macOS
    mkdir -p RhythmGameUtilities/Libs/macOS

    cp build/libRhythmGameUtilities.dylib UnityPackage/Libs/macOS
    cp build/libRhythmGameUtilities.dylib RhythmGameUtilities/Libs/macOS

    printf "%sDONE%s\n" "${GREENON}" "${COLOROFF}"

    printf "Building Linux libraries ... "

    docker-compose up --no-deps --build &>/dev/null

    mkdir -p UnityPackage/Libs/Linux
    mkdir -p RhythmGameUtilities/Libs/Linux

    cp build/libRhythmGameUtilities.so UnityPackage/Libs/Linux
    cp build/libRhythmGameUtilities.so RhythmGameUtilities/Libs/Linux

    printf "%sDONE%s\n" "${GREENON}" "${COLOROFF}"

)
