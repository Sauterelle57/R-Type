cmake_minimum_required(VERSION 3.26)
project(map_editor)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.5
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(map_editor
        src/map_editor.cpp
        src/map_editor.hpp)

target_link_libraries(map_editor PRIVATE nlohmann_json::nlohmann_json)
