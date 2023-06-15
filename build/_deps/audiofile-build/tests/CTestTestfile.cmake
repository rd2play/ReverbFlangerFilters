# CMake generated Testfile for 
# Source directory: C:/JUCEProjects/CombFilter/libs/audiofile/tests
# Build directory: C:/JUCEProjects/CombFilter/build/_deps/audiofile-build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(Tests "C:/JUCEProjects/CombFilter/build/_deps/audiofile-build/tests/Debug/Tests.exe")
  set_tests_properties(Tests PROPERTIES  _BACKTRACE_TRIPLES "C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;11;add_test;C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(Tests "C:/JUCEProjects/CombFilter/build/_deps/audiofile-build/tests/Release/Tests.exe")
  set_tests_properties(Tests PROPERTIES  _BACKTRACE_TRIPLES "C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;11;add_test;C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(Tests "C:/JUCEProjects/CombFilter/build/_deps/audiofile-build/tests/MinSizeRel/Tests.exe")
  set_tests_properties(Tests PROPERTIES  _BACKTRACE_TRIPLES "C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;11;add_test;C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(Tests "C:/JUCEProjects/CombFilter/build/_deps/audiofile-build/tests/RelWithDebInfo/Tests.exe")
  set_tests_properties(Tests PROPERTIES  _BACKTRACE_TRIPLES "C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;11;add_test;C:/JUCEProjects/CombFilter/libs/audiofile/tests/CMakeLists.txt;0;")
else()
  add_test(Tests NOT_AVAILABLE)
endif()
