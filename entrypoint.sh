#!/bin/sh

(
    cd /usr/src/app/

    g++ -std=c++17 -shared -fPIC -o build/libRhythmGameUtilities.so includes/RhythmGameUtilities/RhythmGameUtilities.cpp
)

exec "$@"
