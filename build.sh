#!/usr/bin/env bash

set -Eeuo pipefail

command_name="${1:-release}"
shift || true

case "${command_name}" in
    debug|dev|release|release-shared)
        preset="${command_name}"
        ;;
    tests)
        preset="tests"
        ;;
    help|-h|--help)
        cat <<'EOF'
Uso: ./build.sh [debug|dev|release|release-shared|tests] [argumentos de CMake]

  debug           Debug estatico sin tests
  dev             RelWithDebInfo estatico con tests
  release         Release estatico y portable (predeterminado)
  release-shared  Release con biblioteca compartida
  tests           Debug, compila y ejecuta todos los tests

Ejemplo de optimizacion local:
  ./build.sh release -DORDENARENT_NATIVE_OPTIMIZATION=ON
EOF
        exit 0
        ;;
    *)
        echo "Error: configuracion desconocida: ${command_name}" >&2
        exit 2
        ;;
esac

build_dir="out/build/${preset}"
if [[ ! -f "${build_dir}/CMakeCache.txt" ]] &&
   command -v ninja >/dev/null 2>&1 &&
   [[ -z "${CMAKE_GENERATOR:-}" ]]; then
    export CMAKE_GENERATOR="Ninja"
fi

cmake --preset "${preset}" "$@"
cmake --build --preset "${preset}"

if [[ "${preset}" == "tests" || "${preset}" == "dev" ]]; then
    ctest --preset "${preset}"
fi
