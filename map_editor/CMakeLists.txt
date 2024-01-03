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


if (UNIX)
    set(RAYLIB_VERSION 5.0)
    find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
    if (NOT raylib_FOUND) # If there's none, fetch and build raylib
        include(FetchContent)
        FetchContent_Declare(
                raylib
                DOWNLOAD_EXTRACT_TIMESTAMP OFF
                URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        )
        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
            set(FETCHCONTENT_QUIET NO)
            FetchContent_Populate(raylib)
            set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        endif()
    endif()
endif()

if(WIN32)
    if (DEFINED ENV{USERPROFILE})
        set(HOME_DIRECTORY $ENV{USERPROFILE})
        message("Home directory: ${HOME_DIRECTORY}")
    else()
        message(FATAL_ERROR "USERPROFILE environment variable is not defined.")
    endif()
    INCLUDE_DIRECTORIES(
            ${HOME_DIRECTORY}/vcpkg/installed/x64-windows/include
    )
    LINK_DIRECTORIES(
            ${HOME_DIRECTORY}/vcpkg/installed/x64-windows/lib
    )
endif()


add_executable(map_editor
        ../client/src/renderer/Audio.hpp
        ../client/src/renderer/AudioStream.hpp
        ../client/src/renderer/Cursor.hpp
        ../client/src/renderer/Camera.hpp
        ../client/src/renderer/Camera2D.hpp
        ../client/src/renderer/Event.hpp
        ../client/src/renderer/Font.hpp
        ../client/src/renderer/IAudio.hpp
        ../client/src/renderer/IAudioStream.hpp
        ../client/src/renderer/ICamera.hpp
        ../client/src/renderer/ICamera2D.hpp
        ../client/src/renderer/ICursor.hpp
        ../client/src/renderer/IEvent.hpp
        ../client/src/renderer/IFont.hpp
        ../client/src/renderer/IImage.hpp
        ../client/src/renderer/Image.hpp
        ../client/src/renderer/IMaterial.hpp
        ../client/src/renderer/IMesh.hpp
        ../client/src/renderer/IMode.hpp
        ../client/src/renderer/IModel.hpp
        ../client/src/renderer/IModelAnimation.hpp
        ../client/src/renderer/IMusic.hpp
        ../client/src/renderer/IRay.hpp
        ../client/src/renderer/IRenderTexture.hpp
        ../client/src/renderer/IShader.hpp
        ../client/src/renderer/ISound.hpp
        ../client/src/renderer/ITexture.hpp
        ../client/src/renderer/IWave.hpp
        ../client/src/renderer/IWindow.hpp
        ../client/src/renderer/Material.hpp
        ../client/src/renderer/Mesh.hpp
        ../client/src/renderer/Mode.hpp
        ../client/src/renderer/Model.hpp
        ../client/src/renderer/ModelAnimation.hpp
        ../client/src/renderer/Music.hpp
        ../client/src/renderer/Ray.hpp
        ../client/src/renderer/renderer.hpp
        ../client/src/renderer/RenderTexture.hpp
        ../client/src/renderer/Shader.hpp
        ../client/src/renderer/Sound.hpp
        ../client/src/renderer/Texture.hpp
        ../client/src/renderer/Utils.hpp
        ../client/src/renderer/Wave.hpp
        ../client/src/renderer/Window.hpp


        src/map_editor.cpp
        src/map_editor.hpp
        src/LevelGenerator.hpp
        src/LevelGenerator.cpp
        src/ILevelGenerator.hpp
        src/main.cpp
        Tools/Clock/Clock.hpp
        Tools/Clock/IClock.hpp
        Tools/Error/Error.hpp
        Tools/Utils/Utils.cpp
        Tools/Utils/Utils.hpp
        Tools/Vec3/IVec3.hpp
        Tools/Vec3/Vec3.hpp
        Tools/Vec3/Vec3.cpp
        Tools/Vec4/IVec4.hpp
        Tools/Vec4/Vec4.hpp
        Tools/Vec4/Vec4.cpp)

target_link_libraries(map_editor PRIVATE raylib nlohmann_json::nlohmann_json)

target_include_directories(map_editor PRIVATE
        ${CMAKE_SOURCE_DIR}/../client/src/renderer
)


        # Web Configurations
if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    # Tell Emscripten to build an example.html file.
    set_target_properties(map_editor PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(map_editor "-framework IOKit")
    target_link_libraries(map_editor "-framework Cocoa")
    target_link_libraries(map_editor "-framework OpenGL")
endif()

set_target_properties(map_editor PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
