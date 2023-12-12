cmake_minimum_required(VERSION 3.26)
project(rtype)

set(CMAKE_CXX_STANDARD 14)

# Find and link Boost Asio
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.83 REQUIRED COMPONENTS system date_time)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(client/src)
include_directories(client/src/ECS)
include_directories(client/src/ECS/Managers)
include_directories(client/src/ECS/Managers/Components)
include_directories(client/src/ECS/Managers/Entities)
include_directories(client/src/ECS/Managers/Systems)

add_executable(rtype_server
        server/main.cpp
        server/src/ServerController/IServerController.hpp
        server/src/ServerController/ServerController.cpp
        server/src/ServerController/ServerController.hpp
)

include_directories(server/src)
include_directories(server/src/ServerController)

add_executable(rtype_client
        client/src/ECS/Managers/Components/ComponentsManager.hpp
        client/src/ECS/Managers/Entities/EntitiesManager.hpp
        client/src/ECS/Managers/Systems/SystemsManager.hpp
        client/src/main.cpp
)

if (Boost_FOUND)
    target_link_libraries(rtype_server ${Boost_LIBRARIES})
    target_link_libraries(rtype_client ${Boost_LIBRARIES})
endif()