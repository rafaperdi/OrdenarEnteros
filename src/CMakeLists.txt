cmake_minimum_required(VERSION 3.10)
project(OrdenarEnteros LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OrdenarEnteros
    main.cpp
    int_sort.cpp
)

# Incluir directorio actual para que se encuentren los headers
target_include_directories(OrdenarEnteros PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

