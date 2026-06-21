add_executable(OrdenarEnteros main.cpp)
target_link_libraries(OrdenarEnteros PRIVATE OrdenarEnteros::ordenamiento_lib)
ordenar_configure_target(OrdenarEnteros)

install(TARGETS OrdenarEnteros RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
