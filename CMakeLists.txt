cmake_minimum_required(VERSION 3.20)
project(raylib_project C CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# find_package(raylib QUIET)

# if(NOT raylib_FOUND)
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
fetchcontent_declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
fetchcontent_makeavailable(raylib)
# endif(NOT raylib_FOUND)

add_executable(
    raylib_project src/Camera.cpp src/Entities.cpp src/Game.cpp src/main.cpp
                   src/TileMap.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_definitions(
    ${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)
