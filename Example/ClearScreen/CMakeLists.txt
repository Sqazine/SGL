set(EXE_NAME ClearScreen)
file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

find_package(SDL2 CONFIG REQUIRED)
find_package(Assimp CONFIG REQUIRED)
add_executable(${EXE_NAME} ${SRC})
target_link_libraries(${EXE_NAME} PRIVATE SGL Framework SDL2::SDL2 assimp::assimp)
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Framework)