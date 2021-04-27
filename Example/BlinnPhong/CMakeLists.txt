set(EXE_NAME BlinnPhong)
file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

find_package(SDL2 CONFIG REQUIRED)

find_path(STB_INCLUDE_DIRS "stb.h")
add_executable(${EXE_NAME} ${SRC})
target_link_libraries(${EXE_NAME} PRIVATE SGL Framework SDL2::SDL2)
target_include_directories(${EXE_NAME} PRIVATE ${STB_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} )
target_compile_definitions(${EXE_NAME} PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/Assets/")