cmake_minimum_required(VERSION 3.10)

set(VCPKG_ROOT "$ENV{VCPKG_ROOT}" CACHE STRING "")
set(VCPKG_DEFAULT_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(SGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(SGL)
add_subdirectory(Framework)
add_subdirectory(Example/ClearScreen)


