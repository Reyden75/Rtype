cmake_minimum_required(VERSION 3.19)
project(r-type)

add_compile_options(-Wall -g)
include(${CMAKE_CURRENT_LIST_DIR}/Lib/Components/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Lib/Ecs/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Lib/Network/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Lib/UDP/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Lib/Parser/CMakeLists.txt)

include(${CMAKE_CURRENT_LIST_DIR}/client/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/server/CMakeLists.txt)
