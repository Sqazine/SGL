set(EXE_NAME ClearScreen)
file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

find_package(SDL2 CONFIG REQUIRED)

add_executable(${EXE_NAME} ${SRC})
target_link_libraries(${EXE_NAME} PRIVATE SGL Framework SDL2::SDL2 )
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR} )