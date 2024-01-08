/*
** EPITECH PROJECT, 2024
** Entity.hpp
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <cstdint>
#include <bitset>
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace rt
{
    enum ENTITY_TYPE
    {
        PLAYER,
        PLAYER_NY,

        ENEMY,
        CAMERA,

        TILE,
        TILE_BREAKABLE,

        BASIC_SHOT,
        BASIC_ENEMY_SHOT,
        SIN_SHOT
    };

    struct Entity
    {
        std::uint32_t ECSEntity;

        std::bitset<9> signature;

        tls::Vec3 position;
        tls::Vec4 rotation;
        float scale;
        ENTITY_TYPE entityType;
    };
}

#endif /* !ENTITY_HPP_ */