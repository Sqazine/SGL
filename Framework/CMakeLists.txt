set(LIB_NAME Framework)

FILE(GLOB FRAMEWORK_DIR "*.h" "*.cpp")

source_group("" FILES ${FRAMEWORK_DIR})

file(MAKE_DIRECTORY ${SDL2_SOURCE_DIR}/include/SDL2)
file(GLOB SDL_HEADERS ${SDL2_SOURCE_DIR}/include/*.h)
foreach(header ${SDL_HEADERS})
    get_filename_component(header_name ${header} NAME)
    configure_file(${header} ${SDL2_SOURCE_DIR}/include/SDL2/${header_name} COPYONLY)
endforeach()


add_library(${LIB_NAME} STATIC ${FRAMEWORK_DIR})

target_link_libraries(${LIB_NAME} PRIVATE SGL SDL2-static)
target_include_directories(${LIB_NAME} PUBLIC 
    ${SDL2_SOURCE_DIR}/include
)
target_include_directories(${LIB_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/Framework
)