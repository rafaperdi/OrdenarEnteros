#!/usr/bin/env bash

set -Eeuo pipefail

if [[ ! -f "out/build/tests/CMakeCache.txt" ]] &&
   command -v ninja >/dev/null 2>&1 &&
   [[ -z "${CMAKE_GENERATOR:-}" ]]; then
    export CMAKE_GENERATOR="Ninja"
fi

cmake --preset tests "$@"
cmake --build --preset tests
ctest --preset tests
