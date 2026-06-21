set(
    ORDENARENT_EXAMPLES
    ejemplo1_basico
    ejemplo2_strings
    ejemplo3_objetos
    ejemplo4_complejos
)

foreach(example_name IN LISTS ORDENARENT_EXAMPLES)
    add_executable("${example_name}" "${example_name}.cpp")
    target_link_libraries("${example_name}" PRIVATE OrdenarEnteros::ordenamiento_lib)
    ordenar_configure_target("${example_name}")
    set_target_properties(
        "${example_name}"
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${ORDENARENT_RUNTIME_OUTPUT_DIRECTORY}/examples"
    )
    foreach(config Debug Release RelWithDebInfo MinSizeRel)
        string(TOUPPER "${config}" config_upper)
        set_target_properties(
            "${example_name}"
            PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_${config_upper} "${ORDENARENT_RUNTIME_OUTPUT_DIRECTORY}/examples"
        )
    endforeach()
endforeach()
