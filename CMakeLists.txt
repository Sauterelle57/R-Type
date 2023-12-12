cmake_minimum_required(VERSION 3.26)
project(rtype)

set(CMAKE_CXX_STANDARD 20)

set(RAYLIB_VERSION 4.5.0)
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

include_directories(client/src)
include_directories(client/include)
include_directories(Tools/ECS)
include_directories(Tools/ECS/Managers)
include_directories(Tools/ECS/Managers/Components)
include_directories(Tools/ECS/Managers/Entities)
include_directories(Tools/ECS/Managers/Systems)
include_directories(Tools/ECS/Managers/Coordinator)
include_directories(Tools/Vec3)
include_directories(Tools/Vec4)
include_directories(Tools/Utils)
include_directories(Tools/Error)

add_executable(rtype_server
        Tools/ECS/Managers/Components/ComponentsManager.hpp
        Tools/ECS/Managers/Entities/EntitiesManager.hpp
        Tools/ECS/Managers/Systems/SystemsManager.hpp
        Tools/ECS/Managers/Coordinator/Coordinator.hpp
        Tools/ECS/Managers/Entities/Entity.hpp
        Tools/ECS/Managers/Components/Component.hpp
        Tools/Vec3/Vec3.cpp
        Tools/Vec3/Vec3.hpp
        Tools/Utils/Utils.hpp
        Tools/Utils/Utils.cpp
        server/src/main.cpp
        Tools/Vec4/Vec4.cpp
        Tools/Error/Error.hpp
        Tools/ECS/Managers/Components/ComponentArray.hpp
        Tools/ECS/Managers/Systems/System.hpp
)
add_executable(rtype_client
        Tools/ECS/Managers/Components/ComponentsManager.hpp
        Tools/ECS/Managers/Entities/EntitiesManager.hpp
        Tools/ECS/Managers/Systems/SystemsManager.hpp
        Tools/ECS/Managers/Coordinator/Coordinator.hpp
        Tools/ECS/Managers/Entities/Entity.hpp
        Tools/ECS/Managers/Components/Component.hpp
        Tools/Vec3/Vec3.cpp
        Tools/Vec3/Vec3.hpp
        Tools/Utils/Utils.hpp
        Tools/Utils/Utils.cpp
        client/src/main.cpp
        Tools/Vec4/Vec4.cpp
        Tools/Error/Error.hpp
        Tools/ECS/Managers/Components/ComponentArray.hpp
        Tools/ECS/Managers/Systems/System.hpp
        client/src/renderer/Audio.hpp
        client/src/renderer/AudioStream.hpp
        client/src/renderer/Cursor.hpp
        client/src/renderer/Camera.hpp
        client/src/renderer/Camera2D.hpp
        client/src/renderer/Event.hpp
        client/src/renderer/Font.hpp
        client/src/renderer/IAudio.hpp
        client/src/renderer/IAudioStream.hpp
        client/src/renderer/ICamera.hpp
        client/src/renderer/ICamera2D.hpp
        client/src/renderer/ICursor.hpp
        client/src/renderer/IEvent.hpp
        client/src/renderer/IFont.hpp
        client/src/renderer/IImage.hpp
        client/src/renderer/Image.hpp
        client/src/renderer/IMaterial.hpp
        client/src/renderer/IMesh.hpp
        client/src/renderer/IMode.hpp
        client/src/renderer/IModel.hpp
        client/src/renderer/IModelAnimation.hpp
        client/src/renderer/IMusic.hpp
        client/src/renderer/IRay.hpp
        client/src/renderer/IRenderTexture.hpp
        client/src/renderer/IShader.hpp
        client/src/renderer/ISound.hpp
        client/src/renderer/ITexture.hpp
        client/src/renderer/IWave.hpp
        client/src/renderer/IWindow.hpp
        client/src/renderer/Material.hpp
        client/src/renderer/Mesh.hpp
        client/src/renderer/Mode.hpp
        client/src/renderer/Model.hpp
        client/src/renderer/ModelAnimation.hpp
        client/src/renderer/Music.hpp
        client/src/renderer/Ray.hpp
        client/src/renderer/renderer.hpp
        client/src/renderer/RenderTexture.hpp
        client/src/renderer/Shader.hpp
        client/src/renderer/Sound.hpp
        client/src/renderer/Texture.hpp
        client/src/renderer/Utils.hpp
        client/src/renderer/Wave.hpp
        client/src/renderer/Window.hpp
)


#set(raylib_VERBOSE 1)
target_link_libraries(rtype_client raylib)

# Web Configurations
if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    # Tell Emscripten to build an example.html file.
    set_target_properties(rtype_client PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(rtype_client "-framework IOKit")
    target_link_libraries(rtype_client "-framework Cocoa")
    target_link_libraries(rtype_client "-framework OpenGL")
endif()

set_target_properties(rtype_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
