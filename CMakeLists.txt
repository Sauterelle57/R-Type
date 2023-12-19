cmake_minimum_required(VERSION 3.26)
project(rtype)

set(CMAKE_CXX_STANDARD 20)

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
        TIMEOUT 60
        DOWNLOAD_EXTRACT_TIMESTAMP 1
)

# Specify include directories for Boost.Asio
ExternalProject_Get_Property(BOOSTASIO SOURCE_DIR)
include_directories(${SOURCE_DIR})

add_executable(rtype_server
        # Main
        server/main.cpp
        # Server Controller
        server/src/ServerController/IServerController.hpp
        server/src/ServerController/ServerController.cpp
        server/src/ServerController/ServerController.hpp
        # Game Controller
        server/src/GameController/IGameController.hpp
        server/src/GameController/GameController.hpp
        server/src/GameController/GameController.cpp
        # Asio Wrapper
        server/src/AsioWrapper/IWrapper.hpp
        server/src/AsioWrapper/AsioWrapper.cpp
        server/src/AsioWrapper/AsioWrapper.hpp
)

target_include_directories(rtype_server PRIVATE
    server/src
    server/src/ServerController
    server/src/GameController
    server/src/AsioWrapper
)

include_directories(client/src)
include_directories(client/src/ECS)
include_directories(client/src/ECS/Managers)
include_directories(client/src/ECS/Managers/Components)
include_directories(client/src/ECS/Managers/Entities)
include_directories(client/src/ECS/Managers/Systems)
include_directories(client/src/GameLoop)
include_directories(client/src/UdpClient)


add_executable(rtype_client
        # ECS
        client/src/ECS/Managers/Components/ComponentsManager.hpp
        client/src/ECS/Managers/Entities/EntitiesManager.hpp
        client/src/ECS/Managers/Systems/SystemsManager.hpp
        # Main
        client/src/main.cpp
        # Udp Client
        client/src/UdpClient/UdpClient.hpp
        client/src/UdpClient/UdpClient.cpp
        client/src/UdpClient/IUdpClient.hpp
)

# Link against Boost.Asio (header-only library, no need for separate libraries)
target_link_libraries(rtype_server INTERFACE ${Boost_LIBRARIES})
target_link_libraries(rtype_client INTERFACE ${Boost_LIBRARIES})
