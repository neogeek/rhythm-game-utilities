#!/bin/bash

find ./UnityPackage -type f -name "*" ! -name "*.meta" ! -name ".DS_Store" | while read -r FILE; do
    if ! [ -f "${FILE}.meta" ]; then
        echo "${FILE}.meta does not exist."
        exit 1
    fi
done
