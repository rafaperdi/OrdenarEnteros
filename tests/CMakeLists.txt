find_package(GTest CONFIG QUIET)

if(NOT GTest_FOUND)
    include(FetchContent)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    if(MSVC AND NOT MSVC_STATIC_RUNTIME)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

function(ordenar_add_test target_name source_file)
    add_executable("${target_name}" "${source_file}")
    target_link_libraries(
        "${target_name}"
        PRIVATE
            OrdenarEnteros::ordenamiento_lib
            GTest::gtest_main
    )
    ordenar_configure_target("${target_name}")
    set_target_properties(
        "${target_name}"
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${ORDENARENT_RUNTIME_OUTPUT_DIRECTORY}/tests"
    )
    foreach(config Debug Release RelWithDebInfo MinSizeRel)
        string(TOUPPER "${config}" config_upper)
        set_target_properties(
            "${target_name}"
            PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_${config_upper} "${ORDENARENT_RUNTIME_OUTPUT_DIRECTORY}/tests"
        )
    endforeach()
    gtest_discover_tests("${target_name}" DISCOVERY_TIMEOUT 30)
endfunction()

ordenar_add_test(test_array test_array.cpp)
ordenar_add_test(test_complex test_complex.cpp)
ordenar_add_test(test_sorting test_sorting.cpp)
