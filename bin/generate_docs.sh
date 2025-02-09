#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

REDON=$(tput setaf 1)
GREENON=$(tput setaf 2)
COLOROFF=$(tput sgr0)

(

  mkdir -p build/

  cd "${SCRIPT_DIR}" || exit

  cd ..

  (cat "./Documentation/README.md" && printf '\n') >README.md
  (cat "./Documentation/Platforms.md" && printf '\n') >>README.md
  (cat "./Documentation/Install.md" && printf '\n') >>README.md

  printf "## API\n\n" >>README.md

  (cat "./Documentation/API/Audio/README.md" && printf '\n') >>README.md

  find ./Documentation/API/Audio -type f -name "*.md" -not -name "README.md" | sort -n |
    while read -r FILE; do
      (cat "${FILE}" && printf '\n') >>README.md
    done

  (cat "./Documentation/API/Common/README.md" && printf '\n') >>README.md

  find ./Documentation/API/Common -type f -name "*.md" -not -name "README.md" | sort -n |
    while read -r FILE; do
      (cat "${FILE}" && printf '\n') >>README.md
    done

  (cat "./Documentation/API/Parsers/README.md" && printf '\n') >>README.md

  find ./Documentation/API/Parsers -type f -name "*.md" -not -name "README.md" | sort -n |
    while read -r FILE; do
      (cat "${FILE}" && printf '\n') >>README.md
    done

  (cat "./Documentation/API/Utilities/README.md" && printf '\n') >>README.md

  find ./Documentation/API/Utilities -type f -name "*.md" -not -name "README.md" | sort -n |
    while read -r FILE; do
      (cat "${FILE}" && printf '\n') >>README.md
    done

  (cat "./Documentation/Architecture.md" && printf '\n') >>README.md
  (cat "./Documentation/Git Hooks.md" && printf '\n') >>README.md
  (cat "./Documentation/Testing.md" && printf '\n') >>README.md
  (cat "./Documentation/Build.md" && printf '\n') >>README.md
  (cat "./Documentation/Contributing.md" && printf '\n') >>README.md
  (cat "./Documentation/Community Roadmap.md" && printf '\n') >>README.md
  (cat "./Documentation/Other Projects.md" && printf '\n') >>README.md
  (cat "./Documentation/License.md" && printf '\n') >>README.md

)
