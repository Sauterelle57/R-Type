/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ComponentsManager
*/

#ifndef RTYPE_COMPONENTSTRUCTS_HPP
#define RTYPE_COMPONENTSTRUCTS_HPP

#include <cstdint>
#include <memory>
#include <functional>
#include <vector>
#include <set>
#include "Utils.hpp"
#include "Vec4.hpp"
#include "Vec3.hpp"
#include "Clock.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "Coordinator.hpp"

namespace ECS {
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        LEFT_UP,
        LEFT_DOWN,
        RIGHT_UP,
        RIGHT_DOWN,
        NONE
    };

    enum ParticleType {
        CONE,
        EXPLOSION,
    };

    typedef struct BoundingBox {
        tls::Vec3 min;
        tls::Vec3 max;
    } BoundingBox;

    struct Transform {
        tls::Vec3 position;
        tls::Vec4 rotation;
        float scale;
        BoundingBox bounds;
    };

    struct Projectile {
        std::shared_ptr<float> t = std::make_shared<float>(0.0f);
        Direction direction = ECS::Direction::LEFT;
        std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float> t)> trajectory;
        int damage;
        float speed;
        bool active;
    };

    struct Weapon {
        int damage;
        float speed;
        float durability;
        std::function<void(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos)> create_projectile;
    };

    struct Alive {
        int life;
        int max_life;
    };

    struct Traveling {
        tls::Vec3 speed;
    };

    struct UniqueLink {
        std::string name;
        Entity from;
        Entity to;
    };

    struct MultipleLink {
        std::set<UniqueLink> links;
    };

    inline bool operator<(const UniqueLink& lhs, const UniqueLink& rhs) {
        return lhs.name < rhs.name;
    }

    struct Collider {
        uint8_t team;
    };

}

#endif //RTYPE_COMPONENTSTRUCTS_HPP
