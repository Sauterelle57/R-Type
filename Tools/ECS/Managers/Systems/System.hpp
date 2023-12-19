/*
** EPITECH PROJECT, 2023
** RType
** File description:
** System
*/

#ifndef RTYPE_SYSTEM_HPP
#define RTYPE_SYSTEM_HPP

#include <memory>
#include <set>
#include "Entity.hpp"

namespace ECS {
    class Coordinator;
    class System {
        public:
            System(std::weak_ptr<Coordinator> &coordinator) {
                _coordinator = coordinator;
            };
            ~System() = default;
            void update() {};
            std::set<Entity> _entities;
            std::weak_ptr<Coordinator> _coordinator;
    };
}

#endif //RTYPE_SYSTEM_HPP
