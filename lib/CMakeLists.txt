cmake_minimum_required(VERSION 3.10)

# Crear la librería de ordenamiento
add_library(ordenamiento_lib src/sorting.cpp)

# Establecer propiedades de la librería
set_target_properties(ordenamiento_lib PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

# Incluir directorio de headers
target_include_directories(ordenamiento_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Establecer el estándar C++
target_compile_features(ordenamiento_lib PUBLIC cxx_std_17)

# Visibilidad de símbolos
if(MSVC)
    # Para Windows/MSVC
    target_compile_options(ordenamiento_lib PRIVATE /W4)
else()
    # Para compiladores GCC/Clang
    target_compile_options(ordenamiento_lib PRIVATE -Wall -Wextra)
endif()
