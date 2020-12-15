FILE(GLOB EXAMPLE_DIR *)

find_package(SDL2 CONFIG REQUIRED)
find_package(Assimp CONFIG REQUIRED)
add_executable(Example ${EXAMPLE_DIR})

target_link_libraries(Example PRIVATE libSGL SDL2::SDL2 assimp::assimp)