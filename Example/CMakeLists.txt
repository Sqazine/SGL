set(EXE_NAME Example)
file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_executable(${EXE_NAME} ${SRC})
target_link_libraries(${EXE_NAME} PRIVATE SGL Framework SDL2-static)
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${SDL2_SOURCE_DIR})
target_compile_definitions(${EXE_NAME} PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/Assets/")