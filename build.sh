#!/bin/bash

# Script de compilación rápida para OrdenarEnteros
# Uso: ./build.sh [opción]

set -e

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Funciones
print_header() {
    echo -e "\n${BLUE}╔════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║ OrdenarEnteros - Script de Compilación                         ║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════════════════════════════╝${NC}\n"
}

print_error() {
    echo -e "${RED}✗ Error: $1${NC}"
    exit 1
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_info() {
    echo -e "${YELLOW}ℹ $1${NC}"
}

print_options() {
    echo -e "${BLUE}Opciones disponibles:${NC}"
    echo "  1. dynamic     - Compilar librería dinámica (default, Linux)"
    echo "  2. static      - Compilar librería estática (Linux)"
    echo "  3. debug       - Compilar en modo Debug con libería dinámica"
    echo "  4. release     - Compilar en modo Release optimizado"
    echo "  5. windows     - Compilar para Windows (dinámica)"
    echo "  6. windows-s   - Compilar para Windows (estática)"
    echo "  7. clean       - Limpiar build"
    echo "  8. all         - Compilar todas las versiones"
    echo "  9. help        - Mostrar esta ayuda"
    echo ""
}

# Función de compilación
compile() {
    local build_dir=$1
    local cmake_opts=$2
    local description=$3
    
    print_info "Compilando: $description"
    
    rm -rf "$build_dir"
    mkdir -p "$build_dir"
    cd "$build_dir"
    
    if cmake .. $cmake_opts >/dev/null 2>&1; then
        if cmake --build . >/dev/null 2>&1; then
            print_success "Compilación completada: $description"
            echo -e "  Ejecutable: ${GREEN}$build_dir/bin/OrdenarEnteros${NC}"
            cd ..
            return 0
        else
            print_error "Fallo en cmake --build"
        fi
    else
        print_error "Fallo en cmake configuration"
    fi
}

# Main
main() {
    print_header
    
    if [ $# -eq 0 ]; then
        print_info "Usando opción default: dynamic (Linux dinámica)"
        OPTION="dynamic"
    else
        OPTION=$1
    fi
    
    case $OPTION in
        1|dynamic)
            compile "build" "-DTARGET_PLATFORM=Linux -DBUILD_SHARED_LIBS=ON" \
                    "Linux + Librería Dinámica (.so)"
            ;;
        
        2|static)
            compile "build_static" "-DTARGET_PLATFORM=Linux -DBUILD_SHARED_LIBS=OFF" \
                    "Linux + Librería Estática (.a)"
            ;;
        
        3|debug)
            compile "build_debug" "-DTARGET_PLATFORM=Linux -DCMAKE_BUILD_TYPE=Debug" \
                    "Linux + Debug + Dinámica"
            ;;
        
        4|release)
            compile "build_release" "-DTARGET_PLATFORM=Linux -DCMAKE_BUILD_TYPE=Release" \
                    "Linux + Release Optimizado + Dinámica"
            ;;
        
        5|windows)
            compile "build_windows" "-DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=ON" \
                    "Windows + Librería Dinámica (.dll)"
            ;;
        
        6|windows-s)
            compile "build_windows_static" "-DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=OFF" \
                    "Windows + Librería Estática (.lib)"
            ;;
        
        7|clean)
            print_info "Limpiando builds..."
            rm -rf build build_* >/dev/null 2>&1
            print_success "Limpieza completada"
            ;;
        
        8|all)
            print_info "Compilando TODAS las versiones..."
            compile "build" "-DTARGET_PLATFORM=Linux -DBUILD_SHARED_LIBS=ON" \
                    "Linux + Dinámica"
            compile "build_static" "-DTARGET_PLATFORM=Linux -DBUILD_SHARED_LIBS=OFF" \
                    "Linux + Estática"
            compile "build_debug" "-DTARGET_PLATFORM=Linux -DCMAKE_BUILD_TYPE=Debug" \
                    "Linux + Debug"
            compile "build_windows" "-DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=ON" \
                    "Windows + Dinámica"
            compile "build_windows_static" "-DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=OFF" \
                    "Windows + Estática"
            ;;
        
        9|help|-h|--help)
            print_options
            ;;
        
        *)
            print_error "Opción no reconocida: $OPTION"
            print_options
            exit 1
            ;;
    esac
    
    echo ""
    print_success "Proceso completado"
    echo ""
}

# Ejecutar main
main "$@"
