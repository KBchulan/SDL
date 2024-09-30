cmake_minimum_required(VERSION 3.24)

project(lowr_protect)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(lowr_protect ${SRC_LIST})

target_include_directories(lowr_protect PUBLIC ${SDL3_INCLUDE_DIRS})
target_link_libraries(lowr_protect PUBLIC ${SDL3_LIBRARIES})