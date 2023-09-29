cmake_minimum_required(VERSION 3.19)

project(r-type_server)

if (NOT DEFINED asio_SOURCE_DIR)
    include(FetchContent)
    FetchContent_Declare(asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-16-1
    )
    FetchContent_MakeAvailable(asio)

    include_directories("${asio_SOURCE_DIR}/asio/include")

endif()

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(SRC
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/Server.cpp
        ${SRC_DIR}/Room.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

target_link_libraries(${PROJECT_NAME} UDP)
target_link_libraries(${PROJECT_NAME} Components)
target_link_libraries(${PROJECT_NAME} Parser)