cmake_minimum_required(VERSION 3.10)

# Crear ejemplos
set(EXAMPLES
    ejemplo1_basico
    ejemplo2_strings
    ejemplo3_objetos
)

foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    
    # Vincular con la librería de ordenamiento
    target_link_libraries(${EXAMPLE} PRIVATE ordenamiento_lib)
    
    # Incluir headers de la librería
    target_include_directories(${EXAMPLE} PRIVATE 
        ${CMAKE_SOURCE_DIR}/lib/include
    )
    
    # Establecer el estándar C++
    target_compile_features(${EXAMPLE} PRIVATE cxx_std_17)
    
    # Configurar opciones de compilación
    if(MSVC)
        target_compile_options(${EXAMPLE} PRIVATE /W4)
    else()
        target_compile_options(${EXAMPLE} PRIVATE -Wall -Wextra)
    endif()
    
    # Colocar en el mismo directorio que el ejecutable principal
    set_target_properties(${EXAMPLE} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples
    )
endforeach()
