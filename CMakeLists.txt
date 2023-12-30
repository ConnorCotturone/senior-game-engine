# jacob curlin
# CMakeLists.txt
# 12/29/2023

cmake_minimum_required(VERSION 3.6.0)
project(engine VERSION 0.1.0)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/engine.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)