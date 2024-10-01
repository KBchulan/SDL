cmake_minimum_required(VERSION 3.24)

project(lowr_protect)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(PkgConfig REQUIRED)

pkg_search_module(SDL2_GFX REQUIRED SDL2_gfx)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_executable(lowr_protect ${SRC_LIST})

target_include_directories(lowr_protect PUBLIC 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    )
    
target_link_libraries(lowr_protect PUBLIC 
    SDL2::SDL2
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    ${SDL2_GFX_LIBRARIES}
    )

target_compile_options(lowr_protect PUBLIC ${SDL2_CFLAGS_OTHER})