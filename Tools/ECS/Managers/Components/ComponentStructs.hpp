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
#include "Utils.hpp"
#include "Vec4.hpp"
#include "Vec3.hpp"
#include "renderer/IModel.hpp"
#include "renderer/ITexture.hpp"
#include "Clock.hpp"
#include "Entity.hpp"
#include "Components.hpp"

namespace ECS {
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };

    enum ParticleType {
        CONE,
        EXPLOSION,
    };

    struct Transform {
        tls::Vec3 position;
        tls::Vec4 rotation;
        float scale;
    };

    struct Model {
        std::shared_ptr<RL::IModel> model;
        std::shared_ptr<RL::ITexture> texture;
    };

    struct Player {
        int key_up;
        int key_down;
        int key_left;
        int key_right;
        int key_shoot;
        int key_validate;
        int key_cancel;
        int key_settings;
    };

    struct Particle {
        tls::Vec3 position;
        tls::Vec3 speed;
        float alpha;
        bool active;
    };

    struct Particles {
        std::vector<Particle> particles;
        std::shared_ptr<RL::ZTexture> texture;
        ParticleType type;
        Direction direction;
        float speed;
        float scaleOffset;
        tls::Vec3 positionOffset;
        float lifeTime;
        float spawnRate;
        float spawnTimer;
    };

    struct Projectile {
        std::function<tls::Vec3(tls::Vec3)> trajectory;
        int damage;
        float speed;
    };

    struct Weapon {
        int damage;
        float speed;
        float durability;
        std::function<std::vector<Entity>()> create_projectile;
    };

    struct Alive {
        int life;
        int max_life;
    };

}

#endif //RTYPE_COMPONENTSTRUCTS_HPP
