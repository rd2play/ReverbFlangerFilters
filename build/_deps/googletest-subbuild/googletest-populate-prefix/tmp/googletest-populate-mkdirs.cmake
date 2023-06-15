# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/JUCEProjects/CombFilter/libs/googletest"
  "C:/JUCEProjects/CombFilter/build/_deps/googletest-build"
  "C:/JUCEProjects/CombFilter/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "C:/JUCEProjects/CombFilter/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "C:/JUCEProjects/CombFilter/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "C:/JUCEProjects/CombFilter/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "C:/JUCEProjects/CombFilter/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/JUCEProjects/CombFilter/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/JUCEProjects/CombFilter/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
