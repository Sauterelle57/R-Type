cmake_minimum_required(VERSION 3.26)
project(rtype)

set(CMAKE_CXX_STANDARD 14)

include_directories(client/src)
include_directories(client/src/ECS)
include_directories(client/src/ECS/Managers)
include_directories(client/src/ECS/Managers/Components)
include_directories(client/src/ECS/Managers/Entities)
include_directories(client/src/ECS/Managers/Systems)

add_executable(rtype_server
        server/main.cpp
)
add_executable(rtype_client
        client/src/ECS/Managers/Components/ComponentsManager.hpp
        client/src/ECS/Managers/Entities/EntitiesManager.hpp
        client/src/ECS/Managers/Systems/SystemsManager.hpp
        client/src/main.cpp
)
