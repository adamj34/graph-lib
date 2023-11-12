# CMake generated Testfile for 
# Source directory: /home/addar/graph-lib
# Build directory: /home/addar/graph-lib/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[gralphTests]=] "/home/addar/graph-lib/build/tests/gralphTests")
set_tests_properties([=[gralphTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/addar/graph-lib/CMakeLists.txt;25;add_test;/home/addar/graph-lib/CMakeLists.txt;0;")
subdirs("src")
subdirs("tests")
