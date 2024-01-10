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
#include "ClientController.hpp"
#include "IWrapper.hpp"
#include "Collisions.hpp"

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
        // std::shared_ptr<float> t = std::make_shared<float>(0.0f);
        // Direction direction = ECS::Direction::LEFT;
        // std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float> t)> trajectory;
        int damage;
        float speed;
        bool active;
    };

    struct Trajectory {
        std::shared_ptr<float> t = std::make_shared<float>(0.0f);
        std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float> t)> trajectory;
    };

    struct Weapon {
        int damage;
        float speed;
        float durability;
        std::function<void(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper)> create_projectile;
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
        uint8_t team{};
        bool breakable = true;
        bool movable = true;
        tls::Vec3 velocity;

        tls::BoundingBox bounds;
    };

    struct ClientUpdater {
        std::shared_ptr<rt::IWrapper> wrapper;
        std::shared_ptr<rt::ClientController> clientController;
    };

    struct Type {
        std::string name;
        bool different = false;
        std::string ip;
        int port;
    };

    struct Player {
        tls::Vec3 mooving = {0,0,0};
    };

    struct Shooter {
        bool isShooting = false;
    };

    struct Enemy {
        bool isGoingUp = false;
        bool isTurningLeft = false;
        tls::Clock clock;
    };
}

#endif //RTYPE_COMPONENTSTRUCTS_HPP
