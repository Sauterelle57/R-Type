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
        tls::Vec3 scale;
        BoundingBox bounds;
    };

    struct Projectile {
        float damage;
        float speed;
        bool active;
    };

    struct Trajectory {
        std::shared_ptr<float> t = std::make_shared<float>(0.0f);
        std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float> t)> trajectory;
        bool oriented = false;
    };

    struct Weapon {
        float damage;
        float speed;
        float durability;
        bool autoShoot = false;
        tls::Clock shootFrequency = tls::Clock(2);
        std::function<void(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper, std::shared_ptr<rt::ProtocolController> _pc, ECS::Weapon weapon)> create_projectile;
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
        float life = 100.0;
        float maxLife = 100.0;
        float damage = 0.0;
    };

    struct ClientUpdater {
        std::shared_ptr<rt::ProtocolController> _pc;
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

    struct Parent {
        std::function<void(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, Entity parent)> create_child;
        tls::Clock spawnFrequency = tls::Clock(10);
        int nbChildren = 2;
    };
}

#endif //RTYPE_COMPONENTSTRUCTS_HPP
