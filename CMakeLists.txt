cmake_minimum_required(VERSION 3.10)

project(SGL LANGUAGES CXX)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(3rd/SDL)

add_subdirectory(SGL)
add_subdirectory(Framework)
add_subdirectory(Example)