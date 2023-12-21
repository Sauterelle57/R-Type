/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Components
*/

#ifndef RTYPE_COMPONENTS_HPP
#define RTYPE_COMPONENTS_HPP

#include <cstdint>

namespace ECS {
    using ComponentType = std::uint8_t;

    constexpr ComponentType MAX_COMPONENTS = 128;
}

#endif //RTYPE_COMPONENTS_HPP
