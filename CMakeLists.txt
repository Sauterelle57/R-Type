cmake_minimum_required(VERSION 3.26)
project(rtype)

set(CMAKE_CXX_STANDARD 14)

include_directories(client/src)
include_directories(ECS)
include_directories(ECS/Managers)
include_directories(ECS/Managers/Components)
include_directories(ECS/Managers/Entities)
include_directories(ECS/Managers/Systems)

add_executable(rtype_server
        ECS/Managers/Components/ComponentsManager.hpp
        ECS/Managers/Entities/EntitiesManager.hpp
        ECS/Managers/Systems/SystemsManager.hpp
        server/src/main.cpp
)
add_executable(rtype_client
        ECS/Managers/Components/ComponentsManager.hpp
        ECS/Managers/Entities/EntitiesManager.hpp
        ECS/Managers/Systems/SystemsManager.hpp
        client/src/main.cpp
)
