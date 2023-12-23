cmake_minimum_required(VERSION 3.26)
project(rtype)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)

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

# Include the ExternalProject module
include(ExternalProject)

if(WIN32)
    set(BOOSTASIO_URL "https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.zip")
elseif(UNIX)
    set(BOOSTASIO_URL "https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.tar.gz")
elseif(APPLE)
    set(BOOSTASIO_URL "https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.tar.gz")
endif()

# Find and link Boost Asio
ExternalProject_Add(BOOSTASIO
        URL ${BOOSTASIO_URL}
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/BOOSTASIO
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TIMEOUT 6000
        DOWNLOAD_EXTRACT_TIMESTAMP 1
)

# Specify include directories for Boost.Asio
ExternalProject_Get_Property(BOOSTASIO SOURCE_DIR)
include_directories(${SOURCE_DIR})

add_executable(rtype_server
        server/main.cpp
        # Server Controller
        server/src/ServerController/IServerController.hpp
        server/src/ServerController/ServerController.cpp
        server/src/ServerController/ServerController.hpp
        # Game Controller
        server/src/GameController/IGameController.hpp
        server/src/GameController/GameController.hpp
        server/src/GameController/GameController.cpp
        server/src/Client/Client.cpp
        server/src/Client/Client.hpp
        server/src/Client/IClient.hpp
        server/src/Client/ClientController.hpp
        # Asio Wrapper
        server/src/AsioWrapper/IWrapper.hpp
        server/src/AsioWrapper/AsioWrapper.cpp
        server/src/AsioWrapper/AsioWrapper.hpp
        protocol/Protocol.hpp
        server/Tools/ECS/Managers/Systems/Projectile.hpp
        server/Tools/Vec3/IVec3.hpp
        server/Tools/Vec4/IVec4.hpp
        server/Tools/ECS/Managers/Entities/IEntitiesManager.hpp
        server/Tools/Clock/IClock.hpp
        server/Tools/ECS/Managers/Systems/Traveling.hpp
        server/Tools/ECS/Managers/Systems/MultipleLink.hpp
        server/Tools/ECS/Managers/Components/ComponentStructs.hpp
        server/Tools/ECS/Managers/Components/ComponentsManager.hpp
        server/Tools/ECS/Managers/Components/ComponentArray.hpp
        server/Tools/ECS/Managers/Components/Components.hpp
        server/Tools/ECS/Managers/Entities/EntitiesManager.hpp
        server/Tools/ECS/Managers/Entities/Entity.hpp
        server/Tools/ECS/Managers/Systems/SystemsManager.hpp
        server/Tools/ECS/Managers/Systems/System.hpp
        server/Tools/ECS/Managers/Systems/Move.hpp
        server/Tools/ECS/Managers/Coordinator/Coordinator.hpp
        server/Tools/Utils/Utils.hpp
        server/Tools/Utils/Utils.cpp
        server/Tools/Vec3/Vec3.hpp
        server/Tools/Vec3/Vec3.cpp
        server/Tools/Vec4/Vec4.hpp
        server/Tools/Vec4/Vec4.cpp
        server/Tools/Clock/Clock.hpp
        server/Tools/Error/Error.hpp
        server/Tools/ECS/Managers/Systems/Shoot.hpp
)

add_executable(rtype_client
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
        client/src/main.cpp
        client/src/Core.hpp
        client/src/Core.cpp
        protocol/Protocol.hpp
        client/src/UdpClient/IUdpClient.hpp
        client/src/UdpClient/UdpClient.hpp
        client/src/UdpClient/UdpClient.cpp
        client/src/IListener.hpp
        client/src/Listener.hpp
        client/src/IListener.hpp
        client/src/Listener.hpp
        client/Tools/Vec3/IVec3.hpp
        client/Tools/Vec4/IVec4.hpp
        client/Tools/ECS/Managers/Entities/IEntitiesManager.hpp
        client/Tools/Clock/IClock.hpp
        client/Tools/ECS/Managers/Systems/Projectile.hpp
        client/Tools/ECS/Managers/Systems/Cam.hpp
        client/Tools/ECS/Managers/Systems/Traveling.hpp
        client/Tools/ECS/Managers/Systems/Cam.hpp
        client/Tools/ECS/Managers/Systems/Traveling.hpp
        client/Tools/ECS/Managers/Systems/MultipleLink.hpp
        client/Tools/ECS/Managers/Components/ComponentStructs.hpp
        client/Tools/ECS/Managers/Components/ComponentsManager.hpp
        client/Tools/ECS/Managers/Components/ComponentArray.hpp
        client/Tools/ECS/Managers/Components/Components.hpp
        client/Tools/ECS/Managers/Entities/EntitiesManager.hpp
        client/Tools/ECS/Managers/Entities/Entity.hpp
        client/Tools/ECS/Managers/Systems/SystemsManager.hpp
        client/Tools/ECS/Managers/Systems/System.hpp
        client/Tools/ECS/Managers/Systems/Move.hpp
        client/Tools/ECS/Managers/Systems/DrawModel.hpp
        client/Tools/ECS/Managers/Systems/Play.hpp
        client/Tools/ECS/Managers/Systems/Particle.hpp
        client/Tools/ECS/Managers/Coordinator/Coordinator.hpp
        client/Tools/Utils/Utils.hpp
        client/Tools/Utils/Utils.cpp
        client/Tools/Vec3/Vec3.hpp
        client/Tools/Vec3/Vec3.cpp
        client/Tools/Vec4/Vec4.hpp
        client/Tools/Vec4/Vec4.cpp
        client/Tools/Clock/Clock.hpp
        client/Tools/Error/Error.hpp
        server/Tools/ECS/Managers/Systems/Collider.hpp
)

target_include_directories(rtype_server PRIVATE
        ${CMAKE_SOURCE_DIR}/server/src
        ${CMAKE_SOURCE_DIR}/server/src/ServerController
        ${CMAKE_SOURCE_DIR}/server/src/GameController
        ${CMAKE_SOURCE_DIR}/server/src/AsioWrapper
        ${CMAKE_SOURCE_DIR}/server/src/Client
        ${CMAKE_SOURCE_DIR}/server/Tools/ECS
        ${CMAKE_SOURCE_DIR}/server/Tools/ECS/Managers
        ${CMAKE_SOURCE_DIR}/server/Tools/ECS/Managers/Components
        ${CMAKE_SOURCE_DIR}/server/Tools/ECS/Managers/Entities
        ${CMAKE_SOURCE_DIR}/server/Tools/ECS/Managers/Systems
        ${CMAKE_SOURCE_DIR}/server/Tools/ECS/Managers/Coordinator
        ${CMAKE_SOURCE_DIR}/server/Tools/Vec3
        ${CMAKE_SOURCE_DIR}/server/Tools/Vec4
        ${CMAKE_SOURCE_DIR}/server/Tools/Utils
        ${CMAKE_SOURCE_DIR}/server/Tools/Error
        ${CMAKE_SOURCE_DIR}/server/Tools/Clock
)

target_include_directories(rtype_client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/protocol
        ${CMAKE_SOURCE_DIR}/client/include
        ${CMAKE_SOURCE_DIR}/client/src
        ${CMAKE_SOURCE_DIR}/client/src/ECS
        ${CMAKE_SOURCE_DIR}/client/src/ECS/Managers
        ${CMAKE_SOURCE_DIR}/client/src/ECS/Managers/Components
        ${CMAKE_SOURCE_DIR}/client/src/ECS/Managers/Entities
        ${CMAKE_SOURCE_DIR}/client/src/ECS/Managers/Systems
        ${CMAKE_SOURCE_DIR}/client/src/GameLoop
        ${CMAKE_SOURCE_DIR}/client/src/UdpClient
        ${CMAKE_SOURCE_DIR}/client/Tools/ECS
        ${CMAKE_SOURCE_DIR}/client/Tools
        ${CMAKE_SOURCE_DIR}/client/Tools/Vec3
        ${CMAKE_SOURCE_DIR}/client/Tools/Vec4
        ${CMAKE_SOURCE_DIR}/client/Tools/Clock
        ${CMAKE_SOURCE_DIR}/client/Tools/Utils
        ${CMAKE_SOURCE_DIR}/client/Tools/Error
        ${CMAKE_SOURCE_DIR}/client/Tools/ECS/Managers
        ${CMAKE_SOURCE_DIR}/client/Tools/ECS/Managers/Components
        ${CMAKE_SOURCE_DIR}/client/Tools/ECS/Managers/Entities
        ${CMAKE_SOURCE_DIR}/client/Tools/ECS/Managers/Systems
        ${CMAKE_SOURCE_DIR}/client/Tools/ECS/Managers/Coordinator
)
#set(raylib_VERBOSE 1)

target_link_libraries(rtype_client PRIVATE raylib sfml-network)


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
target_link_libraries(rtype_server INTERFACE ${Boost_LIBRARIES})
#target_link_libraries(rtype_client INTERFACE ${Boost_LIBRARIES})