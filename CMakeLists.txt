cmake_minimum_required(VERSION 3.6.0)
project(cgx VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_CGX "Build the core cpgx engine library" ON)
option(BUILD_EXAMPLES "Build the sandbox example" ON)

if(BUILD_CGX)
    add_subdirectory(cgx)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

