set(EXE_NAME Example)
file(GLOB SRC "*.h" "*.cpp")
file(GLOB SAMPLE_SRC Sample/*.h Sample/*.cpp)
source_group("" FILES ${SRC} ${SAMPLE_SRC})

file(MAKE_DIRECTORY ${SDL2_SOURCE_DIR}/include/SDL2)
file(GLOB SDL_HEADERS ${SDL2_SOURCE_DIR}/include/*.h)
foreach(header ${SDL_HEADERS})
    get_filename_component(header_name ${header} NAME)
    configure_file(${header} ${SDL2_SOURCE_DIR}/include/SDL2/${header_name} COPYONLY)
endforeach()

add_executable(${EXE_NAME} ${SRC})
target_link_libraries(${EXE_NAME} PRIVATE SGL SDL2-static)
target_compile_definitions(${EXE_NAME} PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/Assets/")

target_include_directories(${EXE_NAME} PUBLIC 
    ${SDL2_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR} 
)