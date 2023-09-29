cmake_minimum_required(VERSION 3.10)

project(r-type_client)

if (UNIX)
    message($ENV{VCPKG_DIR})
endif()

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
        ${SRC_DIR}/client/Scenes/Game/Game.cpp
        ${SRC_DIR}/client/Scenes/Menu/Menu.cpp
        ${SRC_DIR}/client/Scenes/Join/Join.cpp
        ${SRC_DIR}/client/Scenes/Create/Create.cpp
        ${SRC_DIR}/client/SceneManager.cpp
        ${SRC_DIR}/client/GameObject/Menu/Buttons/Button.cpp
        ${SRC_DIR}/client/GameObject/Menu/Decors/Decor.cpp
        ${SRC_DIR}/client/GameObject/Menu/Backgrounds/Background.cpp
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/sprites)

if (WIN32)
    execute_process(COMMAND tar -xf ${CMAKE_SOURCE_DIR}/sprites.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/sprites)
elseif(UNIX)
    execute_process(COMMAND unzip -o ${CMAKE_SOURCE_DIR}/sprites.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/sprites)
endif()

add_executable(${PROJECT_NAME} ${SRC})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/sprites)

if (WIN32)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
else()
find_package(X11 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread X11)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_include_directories(${PROJECT_NAME} PUBLIC Components)
target_include_directories(${PROJECT_NAME} PUBLIC EcsLib)
target_link_libraries(${PROJECT_NAME} PUBLIC UDP)

if (WIN32)
    file(COPY ${CMAKE_SOURCE_DIR}/sprites DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_SOURCE_DIR}/levels DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()