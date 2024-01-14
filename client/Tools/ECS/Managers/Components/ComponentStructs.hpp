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
#include "renderer/IMusic.hpp"
#include "renderer/ModelAnimation.hpp"

#include "rlights.h"


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
        tls::Vec3 scale;
        BoundingBox bounds{};
        Transform() = default;
        Transform(float px, float py, float pz, float rx, float ry, float rz, float ra, float sx, float sy, float sz) :
            position(px, py, pz),
            rotation(rx, ry, rz, ra),
            scale(sx, sy, sz)
        {}
        Transform(tls::Vec3 pos, tls::Vec4 rot, tls::Vec3 scale) :
            position(pos),
            rotation(rot),
            scale(scale)
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
        tls::Vec3 scale;
    };

    struct Particles {
        std::vector<Particle> particles;
        std::vector<std::shared_ptr<RL::ZTexture>> texture;
        float speed;
        tls::Vec3 scaleOffset;
        tls::Vec3 positionOffset;
        float lifeTime;
        float spawnRate;
        tls::Clock spawnTimer = tls::Clock(0);
        bool hasStarted = false;
        float surviveChance;
        std::function<void(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle)> initParticle;
        std::function<void(std::shared_ptr<Coordinator> coordinator, Entity entity ,std::shared_ptr<RL::ICamera> camera)> drawParticle;
        std::shared_ptr<RL::IShader> shader;
    };

    struct Projectile {
        float damage;
        float speed;
        bool active = active;
    };

    struct Trajectory {
        std::shared_ptr<float> t = std::make_shared<float>(0.0f);
        std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float> t)> trajectory;
    };

    struct Weapon {
        float damage;
        float speed;
        float durability;
        bool autoShoot = false;
        tls::Clock shootFrequency = tls::Clock(2);
        std::function<void(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos)> create_projectile;
    };

    struct Alive {
        float life;
        float max_life;
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

    struct LightComponent {
        Light light;
    };

    struct ShaderComponent {
        std::shared_ptr<RL::IShader> shader;
    };

    struct Velocity {
        tls::Vec3 speed = {0, 0, 0};
        tls::Vec3 oldPosition = {0, 0, 0};
    };

    struct Bdb {
        BoundingBox bounds = {
            {0, 0, 0},
            {0, 0, 0}
        };
    };

    struct Music {
        std::shared_ptr<RL::IMusic> music;
    };

    struct SlideBar {
        Rectangle bounds;
        std::string textLeft;
        std::string textRight;
        float value;
        float minValue;
        float maxValue;
        std::function<void(float value)> onChange;
    };

    struct CheckBox {
        Rectangle bounds;
        std::string text;
        bool value;
        std::function<void(bool value)> onChange;
    };

    struct Button {
        Rectangle bounds;
        std::string text;
        std::function<void(void)> onClick;
    };

    struct Modal {
        int width;
        int height;
        std::string title;
        int titleWidth;
        bool active = false;
        Color color;
        std::function<void(bool &active)> openClose;
        std::vector<SlideBar> slideBars;
        std::vector<CheckBox> checkBoxes;
        std::vector<Button> buttons;
    };

    struct Animation {
        int animsCount = 0;
        unsigned int animIndex = 0;
        int animCurrentFrame = 0;
        std::shared_ptr<RL::ZModelAnimation> modelAnimation;
    };
}

#endif //RTYPE_COMPONENTSTRUCTS_HPP
