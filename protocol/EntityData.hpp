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
#include "../server/Tools/collisions/Collisions.hpp"

namespace rt
{
    enum ENTITY_TYPE
    {
        PLAYER,
        PLAYER_NY,

        ENEMY,
        ENEMY2,
        FLOOR_ENEMY,
        CAMERA,

        TILE,
        TILE_BREAKABLE,

        BASIC_SHOT,
        BASIC_ENEMY_SHOT,
        SIN_SHOT,

        BDB,
        BOSS,
        CHILD
    };

    struct Entity
    {
        std::uint32_t ECSEntity;

        std::bitset<15> signature;

        tls::Vec3 position;
        tls::Vec4 rotation;
        tls::Vec3 scale;
        ENTITY_TYPE entityType;
        tls::BoundingBox bounds;
    };
}

#endif /* !ENTITY_HPP_ */