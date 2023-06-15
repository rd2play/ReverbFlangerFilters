# $ mkcir build
# $ cmake -S . -B build
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(CombFilter)

set(CMAKE_CXX_STANDARD 23)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# download CPM
set(CPM_DOWNLOAD_VERSION 0.34.0)
set(CPM_DOWNLOAD_LOCATION "${LIB_DIR}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
  file(DOWNLOAD
       https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
       ${CPM_DOWNLOAD_LOCATION}
  )
endif()

include(${CPM_DOWNLOAD_LOCATION})
# end download CPM

# add googletest
CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest    
    VERSION 1.13.0
    SOURCE_DIR ${LIB_DIR}/googletest
)

# https://github.com/adamstark/AudioFile
CPMAddPackage(
    NAME audiofile
    GITHUB_REPOSITORY adamstark/AudioFile    
    GIT_TAG 1.1.1
    SOURCE_DIR ${LIB_DIR}/audiofile
)