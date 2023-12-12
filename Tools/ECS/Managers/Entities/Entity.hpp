/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ComponentsManager
*/

#ifndef RTYPE_ENTITY_HPP
#define RTYPE_ENTITY_HPP

#include <cstdint>
#include <bitset>
#include "Component.hpp"

namespace ECS {
    using Entity = std::uint32_t;

    const Entity MAX_ENTITIES = 100;

    using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif //RTYPE_ENTITY_HPP
