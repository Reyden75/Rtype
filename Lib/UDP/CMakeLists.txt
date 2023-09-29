cmake_minimum_required(VERSION 3.19)
project(UDP)

set(HEADERS ${CMAKE_CURRENT_LIST_DIR}/includes)
set(SRC 
        ${CMAKE_CURRENT_LIST_DIR}/src/UDP.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Route.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Router.cpp
    )

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

add_library(${PROJECT_NAME} ${SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC Network)
