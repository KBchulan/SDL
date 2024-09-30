cmake_minimum_required(VERSION 3.24)

project(lowr_protect)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_executable(lowr_protect ${SRC_LIST})

target_include_directories(lowr_protect PUBLIC 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    )
    
target_link_libraries(lowr_protect PUBLIC 
    SDL2::SDL2
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    )