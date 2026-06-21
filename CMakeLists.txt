cmake_minimum_required(VERSION 3.10)

option(MSVC_STATIC_RUNTIME "Enlazar estáticamente el runtime de MSVC (/MT)" OFF)
if(MSVC_STATIC_RUNTIME AND POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

project(OrdenarEnteros VERSION 1.0.0 LANGUAGES CXX)

# ============================================================================
# Configuración Global
# ============================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Opciones de Compilación (CONFIGURABLES)
# ============================================================================

# Opción 1: Tipo de Librería
option(BUILD_SHARED_LIBS "Construir librería dinámica (.so/.dll) - ON, o estática - OFF" ON)

# Opción 2: Plataforma Destino
set(TARGET_PLATFORM "Linux" CACHE STRING "Plataforma destino: Linux o Windows")
set_property(CACHE TARGET_PLATFORM PROPERTY STRINGS "Linux" "Windows")

# Opción 3: Ruta de salida del ejecutable
set(EXECUTABLE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Directorio de salida para ejecutables")

# Opción 4: Ruta de salida de librerías
set(LIBRARY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Directorio de salida para librerías")

# Opción 5: Habilitar tests unitarios
option(BUILD_TESTS "Compilar tests unitarios con Google Test" ON)

# Opción 6: Enlazar estáticamente el runtime de MSVC para distribuir en Windows
if(MSVC AND MSVC_STATIC_RUNTIME)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# ============================================================================
# Configuración por Plataforma
# ============================================================================

if(TARGET_PLATFORM STREQUAL "Windows")
    message(STATUS "✓ Compilando para Windows")
    
    # En Windows, MSVC es típicamente el compilador
    if(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    endif()
    
    # Extensiones de biblioteca para Windows
    set(LIB_PREFIX "")
    set(LIB_EXTENSION ".dll")
    
elseif(TARGET_PLATFORM STREQUAL "Linux")
    message(STATUS "✓ Compilando para Linux")
    
    # En Linux, típicamente GCC o Clang
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    endif()
    
    # Extensiones de biblioteca para Linux
    set(LIB_PREFIX "lib")
    set(LIB_EXTENSION ".so")
else()
    message(FATAL_ERROR "✗ Plataforma no reconocida: ${TARGET_PLATFORM}")
endif()

# ============================================================================
# Configuración del Tipo de Librería
# ============================================================================

if(BUILD_SHARED_LIBS)
    message(STATUS "✓ Compilando librería DINÁMICA (${LIB_PREFIX}ordenamiento_lib${LIB_EXTENSION})")
    set(LIB_TYPE SHARED)
else()
    message(STATUS "✓ Compilando librería ESTÁTICA (${LIB_PREFIX}ordenamiento_lib.a)")
    set(LIB_TYPE STATIC)
endif()

# ============================================================================
# Establecer directorios de salida
# ============================================================================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBRARY_OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${LIBRARY_OUTPUT_DIR}")

# ============================================================================
# Subdirectorios
# ============================================================================

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(examples)

# Agregar tests si está habilitado
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ============================================================================
# Resumen de Configuración
# ============================================================================

message(STATUS "")
message(STATUS "╔════════════════════════════════════════════════════════════════╗")
message(STATUS "║         OrdenarEnteros - Configuración Compilación             ║")
message(STATUS "╠════════════════════════════════════════════════════════════════╣")
message(STATUS "║ Plataforma Destino:  ${TARGET_PLATFORM}")
message(STATUS "║ Tipo de Librería:    ${LIB_TYPE}")
message(STATUS "║ Estándar C++:        ${CMAKE_CXX_STANDARD}")
message(STATUS "║ Compilador:          ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "║ Tipo de Compilación: ${CMAKE_BUILD_TYPE}")
message(STATUS "║ Executables:         ${EXECUTABLE_OUTPUT_DIR}")
message(STATUS "║ Librerías:           ${LIBRARY_OUTPUT_DIR}")
message(STATUS "║ Tests Unitarios:     ${BUILD_TESTS}")
message(STATUS "╚════════════════════════════════════════════════════════════════╝")
message(STATUS "")

# ============================================================================
# Instrucciones de Uso
# ============================================================================

message(STATUS "Instrucciones de compilación:")
message(STATUS "")
message(STATUS "Compilación por defecto (Dinámica/Linux):")
message(STATUS "  cmake -B build && cmake --build build")
message(STATUS "")
message(STATUS "Compilación con librería estática:")
message(STATUS "  cmake -B build -DBUILD_SHARED_LIBS=OFF && cmake --build build")
message(STATUS "")
message(STATUS "Compilación para Windows (dinámica):")
message(STATUS "  cmake -B build -DTARGET_PLATFORM=Windows && cmake --build build")
message(STATUS "")
message(STATUS "Compilación para Windows (estática):")
message(STATUS "  cmake -B build -DTARGET_PLATFORM=Windows -DBUILD_SHARED_LIBS=OFF && cmake --build build")
message(STATUS "")
message(STATUS "Compilación en modo Debug:")
message(STATUS "  cmake -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build")
message(STATUS "")
message(STATUS "Compilación en modo Release:")
message(STATUS "  cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build")
message(STATUS "")
