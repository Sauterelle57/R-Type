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
#include "Components.hpp"

namespace ECS {
    using Entity = std::uint32_t;

    constexpr Entity MAX_ENTITIES = 200000;

    using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif //RTYPE_ENTITY_HPP
