cmake_minimum_required(VERSION 3.21)

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

project(
    OrdenarEnteros
    VERSION 1.1.0
    DESCRIPTION "Biblioteca C++17 portable de contenedores, ordenamiento y numeros complejos"
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CheckIPOSupported)
include(CMakePackageConfigHelpers)

# Compatibilidad temporal con la opcion historica BUILD_TESTS.
if(DEFINED BUILD_TESTS AND NOT DEFINED BUILD_TESTING)
    set(BUILD_TESTING "${BUILD_TESTS}" CACHE BOOL "Compilar pruebas unitarias")
endif()
option(BUILD_TESTING "Compilar pruebas unitarias" OFF)
include(CTest)

option(ORDENARENT_BUILD_APP "Compilar la aplicacion principal" ON)
option(ORDENARENT_BUILD_EXAMPLES "Compilar los ejemplos" ON)
option(ORDENARENT_ENABLE_IPO "Habilitar optimizacion interprocedimental en builds optimizadas" ON)
option(ORDENARENT_NATIVE_OPTIMIZATION "Optimizar para la CPU local (reduce portabilidad del binario)" OFF)
option(ORDENARENT_ENABLE_SANITIZERS "Habilitar AddressSanitizer y UndefinedBehaviorSanitizer" OFF)
option(ORDENARENT_WARNINGS_AS_ERRORS "Tratar las advertencias como errores" OFF)
option(MSVC_STATIC_RUNTIME "Enlazar estaticamente el runtime de MSVC (/MT)" OFF)

set(
    ORDENARENT_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/bin"
    CACHE PATH
    "Directorio de salida para ejecutables y DLL"
)
set(
    ORDENARENT_LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/lib"
    CACHE PATH
    "Directorio de salida para bibliotecas"
)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ORDENARENT_RUNTIME_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ORDENARENT_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ORDENARENT_LIBRARY_OUTPUT_DIRECTORY}")

# Los presets usan una carpeta por configuracion, por lo que evitamos que los
# generadores multiconfiguracion anadan otro nivel Debug/Release.
foreach(config Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER "${config}" config_upper)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} "${ORDENARENT_RUNTIME_OUTPUT_DIRECTORY}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_upper} "${ORDENARENT_LIBRARY_OUTPUT_DIRECTORY}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_upper} "${ORDENARENT_LIBRARY_OUTPUT_DIRECTORY}")
endforeach()

if(MSVC AND MSVC_STATIC_RUNTIME)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_library(ordenar_project_options INTERFACE)
target_compile_features(ordenar_project_options INTERFACE cxx_std_17)
install(TARGETS ordenar_project_options EXPORT OrdenarEnterosTargets)

if(MSVC)
    target_compile_options(
        ordenar_project_options
        INTERFACE
            /W4
            /permissive-
            /Zc:__cplusplus
            /utf-8
    )
    if(ORDENARENT_WARNINGS_AS_ERRORS)
        target_compile_options(ordenar_project_options INTERFACE /WX)
    endif()
else()
    target_compile_options(
        ordenar_project_options
        INTERFACE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
    )
    if(ORDENARENT_WARNINGS_AS_ERRORS)
        target_compile_options(ordenar_project_options INTERFACE -Werror)
    endif()
endif()

if(ORDENARENT_NATIVE_OPTIMIZATION)
    if(MSVC)
        target_compile_options(ordenar_project_options INTERFACE $<$<CONFIG:Release,RelWithDebInfo>:/arch:AVX2>)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(ordenar_project_options INTERFACE $<$<CONFIG:Release,RelWithDebInfo>:-march=native>)
    endif()
endif()

if(ORDENARENT_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(ordenar_project_options INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(ordenar_project_options INTERFACE -fsanitize=address,undefined)
    else()
        message(WARNING "Los sanitizers configurados solo estan disponibles con GCC o Clang")
    endif()
endif()

set(ORDENARENT_IPO_AVAILABLE OFF)
if(ORDENARENT_ENABLE_IPO)
    check_ipo_supported(RESULT ORDENARENT_IPO_AVAILABLE OUTPUT ORDENARENT_IPO_ERROR LANGUAGES CXX)
    if(NOT ORDENARENT_IPO_AVAILABLE)
        message(STATUS "IPO/LTO no disponible: ${ORDENARENT_IPO_ERROR}")
    endif()
endif()

function(ordenar_configure_target target_name)
    target_link_libraries("${target_name}" PRIVATE ordenar_project_options)
    if(ORDENARENT_IPO_AVAILABLE)
        set_property(TARGET "${target_name}" PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
        set_property(TARGET "${target_name}" PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE)
        set_property(TARGET "${target_name}" PROPERTY INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE)
    endif()
endfunction()

add_subdirectory(lib)

if(ORDENARENT_BUILD_APP)
    add_subdirectory(app)
endif()

if(ORDENARENT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/OrdenarEnterosConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/OrdenarEnterosConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/OrdenarEnterosConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OrdenarEnteros"
)

install(
    EXPORT OrdenarEnterosTargets
    FILE OrdenarEnterosTargets.cmake
    NAMESPACE OrdenarEnteros::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OrdenarEnteros"
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/OrdenarEnterosConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/OrdenarEnterosConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OrdenarEnteros"
)

if(WIN32)
    set(ORDENARENT_PLATFORM "Windows")
elseif(UNIX)
    set(ORDENARENT_PLATFORM "Linux/Unix")
else()
    set(ORDENARENT_PLATFORM "${CMAKE_SYSTEM_NAME}")
endif()

message(STATUS "")
message(STATUS "OrdenarEnteros ${PROJECT_VERSION}")
message(STATUS "  Sistema:              ${ORDENARENT_PLATFORM} (${CMAKE_SYSTEM_PROCESSOR})")
message(STATUS "  Compilador:           ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Generador:            ${CMAKE_GENERATOR}")
message(STATUS "  Tipo:                 ${CMAKE_BUILD_TYPE}")
message(STATUS "  Biblioteca compartida:${BUILD_SHARED_LIBS}")
message(STATUS "  Aplicacion:           ${ORDENARENT_BUILD_APP}")
message(STATUS "  Ejemplos:             ${ORDENARENT_BUILD_EXAMPLES}")
message(STATUS "  Tests:                ${BUILD_TESTING}")
message(STATUS "  IPO/LTO:              ${ORDENARENT_IPO_AVAILABLE}")
message(STATUS "  Optimizacion nativa:  ${ORDENARENT_NATIVE_OPTIMIZATION}")
message(STATUS "  Runtime MSVC estatico:${MSVC_STATIC_RUNTIME}")
message(STATUS "")
