cmake_minimum_required(VERSION 3.26)
project(rtype)

set(CMAKE_CXX_STANDARD 14)

include_directories(client/src)
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
)
