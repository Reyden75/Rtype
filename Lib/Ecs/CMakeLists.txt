cmake_minimum_required(VERSION 3.19)
project(EcsLib)

set(HEADERS ${CMAKE_CURRENT_LIST_DIR}/includes)

message("Build ${PROJECT_NAME} at ${CMAKE_CURRENT_LIST_DIR}")

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
include_directories(${HEADERS})
