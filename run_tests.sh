#!/bin/bash

# Script para ejecutar todos los tests del proyecto

set -e

BUILD_DIR="build_static"
TESTS_DIR="bin/tests"

echo "======================================================================"
echo "                    EJECUTANDO TESTS UNITARIOS"
echo "======================================================================"
echo ""

# Cambiar al directorio de build
if [ ! -d "$BUILD_DIR" ]; then
    echo "✗ Error: Directorio de build no encontrado: $BUILD_DIR"
    echo "Por favor ejecute primero: mkdir $BUILD_DIR && cd $BUILD_DIR && cmake .. && make"
    exit 1
fi

cd "$BUILD_DIR"

if [ ! -d "$TESTS_DIR" ]; then
    echo "✗ Error: Tests no compilados. Ejecute: make"
    exit 1
fi

# Variables para tracking
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Función para ejecutar un test
run_test() {
    local test_name=$1
    local test_executable=$2
    
    echo ""
    echo "────────────────────────────────────────────────────────────────"
    echo "Ejecutando: $test_name"
    echo "────────────────────────────────────────────────────────────────"
    
    if ./"$test_executable"; then
        PASSED_TESTS=$((PASSED_TESTS + 1))
        echo "✓ $test_name PASSED"
    else
        FAILED_TESTS=$((FAILED_TESTS + 1))
        echo "✗ $test_name FAILED"
    fi
    echo ""
}

# Ejecutar tests de Complex
if [ -f "$TESTS_DIR/test_complex" ]; then
    run_test "test_complex" "$TESTS_DIR/test_complex"
else
    echo "✗ test_complex no encontrado"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi

# Ejecutar tests de Array
if [ -f "$TESTS_DIR/test_array" ]; then
    run_test "test_array" "$TESTS_DIR/test_array"
else
    echo "✗ test_array no encontrado"
    FAILED_TESTS=$((FAILED_TESTS + 1))
fi

# Resumen
echo ""
echo "======================================================================"
echo "                          RESUMEN DE TESTS"
echo "======================================================================"
echo ""
echo "Tests Ejecutados: $((PASSED_TESTS + FAILED_TESTS))"
echo "✓ Pasados: $PASSED_TESTS"
echo "✗ Fallidos: $FAILED_TESTS"
echo ""

if [ $FAILED_TESTS -eq 0 ]; then
    echo "======================================================================"
    echo "                   ✓ TODOS LOS TESTS PASARON"
    echo "======================================================================"
    exit 0
else
    echo "======================================================================"
    echo "                 ✗ ALGUNOS TESTS FALLARON"
    echo "======================================================================"
    exit 1
fi
