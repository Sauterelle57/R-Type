/*
** EPITECH PROJECT, 2023
** RType
** File description:
** System
*/

#ifndef RTYPE_SYSTEM_HPP
#define RTYPE_SYSTEM_HPP

#include "Entity.hpp"
#include <set>

namespace ECS {
    class System {
        public:
            std::set<Entity> _entities;
    };
}

#endif //RTYPE_SYSTEM_HPP
