cmake_minimum_required(VERSION 3.19)
project(Parser)

set(HEADERS ${CMAKE_CURRENT_LIST_DIR}/includes)

message("Build ${PROJECT_NAME} at ${CMAKE_CURRENT_LIST_DIR}")

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

if (NOT DEFINED ENV{VCPKG_DIR})
    message(FATAL_ERROR "VCPKG_DIR environment is not define.")
endif()

include($ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

find_package(tinyxml CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} INTERFACE unofficial-tinyxml::unofficial-tinyxml)

include_directories(${HEADERS})
