cmake_minimum_required(VERSION 3.19)
project(Network)

set(HEADERS ${CMAKE_CURRENT_LIST_DIR}/includes)

message("Build ${PROJECT_NAME} at ${CMAKE_CURRENT_LIST_DIR}")

if (NOT DEFINED asio_SOURCE_DIR)
    include(FetchContent)
    FetchContent_Declare(asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-16-1
    )
    FetchContent_MakeAvailable(asio)

    include_directories("${asio_SOURCE_DIR}/asio/include")
endif()

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_include_directories(${PROJECT_NAME} INTERFACE ${HEADERS})
