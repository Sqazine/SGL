set(EXE_NAME Phong)
file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

find_package(SDL2 CONFIG REQUIRED)
add_executable(${EXE_NAME} ${SRC})
target_link_libraries(${EXE_NAME} PRIVATE SGL Engine SDL2::SDL2)
target_include_directories(${EXE_NAME} PRIVATE ${STB_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} )