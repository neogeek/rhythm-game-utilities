#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    g++ -std=c++17 -shared -fPIC -arch arm64 -undefined dynamic_lookup -o rhythmgameutilities.so lua_bindings.cpp \
        -I../include \
        -I/opt/homebrew/Cellar/lua/5.4.8/include

)
