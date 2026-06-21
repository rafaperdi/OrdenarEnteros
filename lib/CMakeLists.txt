add_library(
    ordenamiento_lib
    src/complex.cpp
    src/sorting.cpp
)
add_library(OrdenarEnteros::ordenamiento_lib ALIAS ordenamiento_lib)

target_include_directories(
    ordenamiento_lib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(ordenamiento_lib PUBLIC cxx_std_17)
ordenar_configure_target(ordenamiento_lib)

set_target_properties(
    ordenamiento_lib
    PROPERTIES
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION_MAJOR}"
        WINDOWS_EXPORT_ALL_SYMBOLS ON
)

install(
    TARGETS ordenamiento_lib
    EXPORT OrdenarEnterosTargets
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
