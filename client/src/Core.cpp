/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Core
*/

#include "renderer/Window.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Cursor.hpp"
#include "renderer/Event.hpp"
#include "renderer/Model.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Utils.hpp"
#include "Core.hpp"
#include "Utils.hpp"

namespace RT {

    void Core::checkCollision(ECS::Entity entity1, ECS::Entity entity2) {
        auto coordinatorPtr = _coordinator;
        if (!coordinatorPtr)
            return;

        auto &collision1 = coordinatorPtr->getComponent<ECS::Transform>(entity1);
        auto &collision2 = coordinatorPtr->getComponent<ECS::Transform>(entity2);

        std::cout << collision1.position._x << " " << collision2.position._x << std::endl;
        if (RL::Utils::checkCollisionBoxes(collision1.bounds, collision2.bounds))
            std::cout << "Collision detected between entities" << std::endl;
    }

    Core::Core()
    {
        _window = std::make_shared<RL::ZWindow>(_screenWidth, _screenHeight, "R TYPE");

        _cursor = std::make_shared<RL::ZCursor>();
        _cursor->disable();
        _event = std::make_shared<RL::ZEvent>();
        _event->setExitKey(KEY_F4);

        _coordinator = std::make_shared<ECS::Coordinator>();

        RL::Utils::setTargetFPS(60);
    }

    void Core::initEntities() {
        std::shared_ptr<RL::ZModel> model = std::make_shared<RL::ZModel>("./client/resources/models/ship.glb");
        Matrix matr = MatrixIdentity();
        matr = MatrixMultiply(matr, MatrixRotateY(90 * DEG2RAD));
        matr = MatrixMultiply(matr, MatrixRotateZ(90 * DEG2RAD));
        model.get()->_model->transform = matr;

        _entities.insert(_entities.end(), _coordinator->createEntity());
        _playerId = *_entities.rbegin();
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Model {
                .model = model,
//                .texture = std::make_shared<RL::ZTexture>("./client/resources/images/duck_text.png"),
            }
        );
        _coordinator->addComponent(
                *_entities.rbegin(),
                ECS::Traveling {
                        .speed = {0.1, 0, 0}
                }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {0, 0, 0},
                .rotation = {0, 0, 0, 0},
                .scale = 0.5f
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Player {
                .key_up = KEY_W,
                .key_down = KEY_S,
                .key_left = KEY_A,
                .key_right = KEY_D,
                .key_shoot = KEY_F,
                .key_validate = KEY_ENTER,
                .key_cancel = KEY_DELETE,
                .key_settings = KEY_TAB
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Weapon {
                .damage = 1,
                .speed = 1,
                .durability = 1,
                .create_projectile = ECS::Shoot::basicShot
            }
        );

        _camera = std::make_shared<RL::ZCamera>();
        _camera->setPosition({ 0.0f, 10.0f, 100.0f });
        _camera->setTarget({ 0.0f, 10.0f, 0.0f });
        _camera->setUp({ 0.0f, 1.0f, 0.0f });
        _camera->setFovy(30.0f);
        _camera->setProjection(CAMERA_PERSPECTIVE);

        _entities.insert(_entities.end(), _coordinator->createEntity());
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Cam {
                .camera = _camera
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {0, 10, 100},
                .rotation = {0, 0, 0, 0},
                .scale = 1.0f
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.1, 0, 0}
            }
        );

        _entities.insert(_entities.end(), _coordinator->createEntity());
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {0, 0, 0},
                .rotation = {0, 0, 0, 0},
                .scale = 1.0f
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::SkyBox {}
        );
        _systems._systemSkyBox->init(*_entities.rbegin(), true, "./client/resources/images/skybox.hdr");

//        _entities.insert(_entities.end(), _coordinator->createEntity());
//        _coordinator->addComponent(
//            *_entities.rbegin(),
//            ECS::Model {
//                .model = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb"),
//            }
//        );
//        _coordinator->addComponent(
//            *_entities.rbegin(),
//            ECS::Transform {
//                .position = {0, 5, 0},
//                .rotation = {0, 0, 0, 0},
//                .scale = 1.0f
//            }
//        );
    }

    void Core::initComponents() {
        _coordinator->init();

        _coordinator->registerComponent<ECS::Transform>();
        _coordinator->registerComponent<ECS::Model>();
        _coordinator->registerComponent<ECS::Player>();
        _coordinator->registerComponent<ECS::Particles>();
        _coordinator->registerComponent<ECS::Projectile>();
        _coordinator->registerComponent<ECS::Weapon>();
        _coordinator->registerComponent<ECS::Cam>();
        _coordinator->registerComponent<ECS::Traveling>();
        _coordinator->registerComponent<ECS::SkyBox>();
    }

    void Core::initSystem() {
        _systems._systemMove = _coordinator->registerSystem<ECS::Move>();
        _systems._systemDrawModel = _coordinator->registerSystem<ECS::DrawModel>();
        _systems._systemPlayer = _coordinator->registerSystem<ECS::Play>();
        _systems._systemParticles = _coordinator->registerSystem<ECS::ParticleSystem>();
        _systems._systemShoot = _coordinator->registerSystem<ECS::Shoot>();
        _systems._systemProjectile = _coordinator->registerSystem<ECS::ProjectileSystem>();
        _systems._systemCamera = _coordinator->registerSystem<ECS::CamSystem>();
        _systems._systemTraveling = _coordinator->registerSystem<ECS::TravelingSystem>();
        _systems._systemSkyBox = _coordinator->registerSystem<ECS::SkyBoxSystem>();

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            _coordinator->setSystemSignature<ECS::Move>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Model>());
            _coordinator->setSystemSignature<ECS::DrawModel>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Model>());
            signature.set(_coordinator->getComponentType<ECS::Player>());
            _coordinator->setSystemSignature<ECS::Play>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Particles>());
            _coordinator->setSystemSignature<ECS::ParticleSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Weapon>());
            _coordinator->setSystemSignature<ECS::Shoot>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Projectile>());
            _coordinator->setSystemSignature<ECS::ProjectileSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Cam>());
            _coordinator->setSystemSignature<ECS::CamSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Traveling>());
            _coordinator->setSystemSignature<ECS::TravelingSystem>(signature);
        }
    }

    void Core::loop() {
        initComponents();
        initSystem();
        initEntities();

        std::shared_ptr<RL::ZShader> shader = std::make_shared<RL::ZShader>("./client/resources/shaders/particle.vs", "./client/resources/shaders/particle.fs");
        int glowIntensityLoc = shader->getLocation("glowIntensity");
        float glowIntensity = 3.0f;
        shader->setValue(glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);

        while (!_window->shouldClose()) {
            _window->beginDrawing();
            _window->clearBackground(BLACK);
            _systems._systemCamera->begin();

            _systems._systemDrawModel->update();
            _systems._systemMove->update();
            _systems._systemPlayer->update(_event);
            _systems._systemParticles->update(_camera, shader);
            _systems._systemShoot->update(_event);
            _systems._systemProjectile->update();
            _systems._systemCamera->update();
            _systems._systemTraveling->update();
            _systems._systemSkyBox->update();

            // checkCollision(*_entities.rbegin(), *_entities.rend());

            _window->drawGrid(10, 1.0f);
            _systems._systemCamera->end();
            _window->drawFPS(10, 10);
            _window->endDrawing();
        }
    }
};
