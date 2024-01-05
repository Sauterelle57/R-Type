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
#include "renderer/IModel.hpp"
#include "renderer/ITexture.hpp"
#include "renderer/Texture.hpp"
#include "Clock.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "renderer/ICamera.hpp"
#include "Coordinator.hpp"
#include "renderer/ISound.hpp"
#include "renderer/IShader.hpp"

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

    struct Transform {
        tls::Vec3 position;
        tls::Vec4 rotation;
        float scale;
        BoundingBox bounds{};
        Transform() = default;
        Transform(float px, float py, float pz, float rx, float ry, float rz, float ra, float s) :
            position(px, py, pz),
            rotation(rx, ry, rz, ra),
            scale(s)
        {}
        Transform(tls::Vec3 pos, tls::Vec4 rot, float s) :
            position(pos),
            rotation(rot),
            scale(s)
        {}
    };

    struct Model {
        std::shared_ptr<RL::IModel> model;
        std::shared_ptr<RL::ITexture> texture;
        Color color = WHITE;
    };

    struct Player {
        int key_up = KEY_W;
        int key_down = KEY_S;
        int key_left = KEY_A;
        int key_right = KEY_D;
        int key_shoot = KEY_SPACE;
        int key_validate = KEY_ENTER;
        int key_cancel = KEY_DELETE;
        int key_settings = KEY_TAB;
    };

    struct Particle {
        int id = 0;
        tls::Vec3 position;
        tls::Vec3 speed;
        float alpha;
        bool active;
        float scale;
    };

    struct Particles {
        std::vector<Particle> particles;
        std::vector<std::shared_ptr<RL::ZTexture>> texture;
        float speed;
        float scaleOffset;
        tls::Vec3 positionOffset;
        float lifeTime;
        float spawnRate;
        tls::Clock spawnTimer = tls::Clock(0);
        bool hasStarted = false;
        float surviveChance;
        std::function<void(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle)> initParticle;
        std::function<void(std::shared_ptr<Coordinator> coordinator, Entity entity ,std::shared_ptr<RL::ICamera> camera, std::shared_ptr<RL::IShader> shader)> drawParticle;
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

    struct Cam {
        std::shared_ptr<RL::ICamera> camera;
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

    struct Sound {
        std::shared_ptr<RL::ISound> sound;
        bool loop = false;
        bool alreadyPlayed = false;
    };

    struct SelfDestruct {
        tls::Clock timer;
    };

}

#endif //RTYPE_COMPONENTSTRUCTS_HPP
