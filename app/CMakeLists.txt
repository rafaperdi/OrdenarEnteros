cmake_minimum_required(VERSION 3.10)

# Crear el ejecutable
add_executable(${PROJECT_NAME} main.cpp)

# Vincular con la librería de ordenamiento
target_link_libraries(${PROJECT_NAME} PRIVATE ordenamiento_lib)

# Incluir headers de la librería
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/include
)

# Establecer el estándar C++
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Configurar opciones de compilación
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
