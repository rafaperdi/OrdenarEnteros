cmake_minimum_required(VERSION 3.10)

# ============================================================================
# Descarga e incluye Google Test
# ============================================================================

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0  # Versión estable de Google Test
)

# No compilar los tests de Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Evitar mensajes de advertencia
set(BUILD_GMOCK OFF CACHE BOOL "")

FetchContent_MakeAvailable(googletest)

# ============================================================================
# Habilitar Testing
# ============================================================================

enable_testing()

# ============================================================================
# Crear Ejecutables de Tests
# ============================================================================

# Test para la clase Complex
add_executable(test_complex test_complex.cpp)
target_link_libraries(test_complex 
    PRIVATE 
        ordenamiento_lib
        GTest::gtest_main
)

target_include_directories(test_complex
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/lib/include
)

target_compile_features(test_complex PRIVATE cxx_std_17)

# Configurar opciones de compilación
if(MSVC)
    target_compile_options(test_complex PRIVATE /W4)
else()
    target_compile_options(test_complex PRIVATE -Wall -Wextra)
endif()

# Registrar el test
add_test(NAME ComplexTests COMMAND test_complex)

# ============================================================================

# Test para la clase Array
add_executable(test_array test_array.cpp)
target_link_libraries(test_array
    PRIVATE
        ordenamiento_lib
        GTest::gtest_main
)

target_include_directories(test_array
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/include
)

target_compile_features(test_array PRIVATE cxx_std_17)

# Configurar opciones de compilación
if(MSVC)
    target_compile_options(test_array PRIVATE /W4)
else()
    target_compile_options(test_array PRIVATE -Wall -Wextra)
endif()

# Registrar el test
add_test(NAME ArrayTests COMMAND test_array)

# ============================================================================
# Configuración de Salida
# ============================================================================

# Colocar ejecutables de tests en directorio específico
set_target_properties(test_complex test_array PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
)

# ============================================================================
# Instrucciones
# ============================================================================

message(STATUS "")
message(STATUS "╔════════════════════════════════════════════════════════════════╗")
message(STATUS "║                   Google Test Configurado                      ║")
message(STATUS "╠════════════════════════════════════════════════════════════════╣")
message(STATUS "║ Para ejecutar TODOS los tests:                                ║")
message(STATUS "║   ctest --output-on-failure                                   ║")
message(STATUS "║   o                                                           ║")
message(STATUS "║   cmake --build . --target test                               ║")
message(STATUS "║                                                              ║")
message(STATUS "║ Para ejecutar tests individuales:                             ║")
message(STATUS "║   ./bin/tests/test_complex                                    ║")
message(STATUS "║   ./bin/tests/test_array                                      ║")
message(STATUS "║                                                              ║")
message(STATUS "║ Para ejecutar un test específico:                             ║")
message(STATUS "║   ./bin/tests/test_complex --gtest_filter=ComplexTest.*       ║")
message(STATUS "╚════════════════════════════════════════════════════════════════╝")
message(STATUS "")
