# CMake generated Testfile for 
# Source directory: /home/rperdi/projects/cplusplus/repos/OrdenarEnteros/tests
# Build directory: /home/rperdi/projects/cplusplus/repos/OrdenarEnteros/build_static/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ComplexTests "/home/rperdi/projects/cplusplus/repos/OrdenarEnteros/build_static/bin/tests/test_complex")
set_tests_properties(ComplexTests PROPERTIES  _BACKTRACE_TRIPLES "/home/rperdi/projects/cplusplus/repos/OrdenarEnteros/tests/CMakeLists.txt;57;add_test;/home/rperdi/projects/cplusplus/repos/OrdenarEnteros/tests/CMakeLists.txt;0;")
add_test(ArrayTests "/home/rperdi/projects/cplusplus/repos/OrdenarEnteros/build_static/bin/tests/test_array")
set_tests_properties(ArrayTests PROPERTIES  _BACKTRACE_TRIPLES "/home/rperdi/projects/cplusplus/repos/OrdenarEnteros/tests/CMakeLists.txt;84;add_test;/home/rperdi/projects/cplusplus/repos/OrdenarEnteros/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
