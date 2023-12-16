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
#include "DrawModel.hpp"
#include "Move.hpp"
#include "Play.hpp"

namespace RT {
    Core::Core()
    {
        _window = std::make_shared<RL::ZWindow>(_screenWidth, _screenHeight, "R TYPE");
        _camera = std::make_shared<RL::ZCamera>();
        _camera->setPosition((Vector3){ 25.0f, 20.0f, 6.0f });
        _camera->setTarget((Vector3){ 0.0f, 8.0f, 0.0f });
        _camera->setUp((Vector3){ 0.0f, 1.0f, 0.0f });
        _camera->setFovy(45.0f);
        _camera->setProjection(CAMERA_PERSPECTIVE);

        _cursor = std::make_shared<RL::ZCursor>();
        _cursor->disable();
        _event = std::make_shared<RL::ZEvent>();
        _event->setExitKey(KEY_F4);

        _coordinator = std::make_shared<ECS::Coordinator>();

        RL::Utils::setTargetFPS(60);
    }

    void Core::initEntities() {
        _entities.resize(ECS::MAX_ENTITIES);
        _entities[0] = _coordinator->createEntity();
        _coordinator->addComponent(
            _entities[0],
            ECS::Transform {
                .position = {100, 0, 100},
                .rotation = {0, 0, 0, 0},
                .scale = 1.0f
            }
        );

        _entities[1] = _coordinator->createEntity();
        _coordinator->addComponent(
            _entities[1],
            ECS::Model {
                .model = std::make_shared<RL::ZModel>("./client/resources/models/ship.glb"),
            }
        );
        _coordinator->addComponent(
            _entities[1],
            ECS::Transform {
                .position = {0, 0, 0},
                .rotation = {0, 0, 0, 0},
                .scale = 0.6f
            }
        );
        _coordinator->addComponent(
            _entities[1],
            ECS::Player {
                .key_up = KEY_Y,
                .key_down = KEY_G,
                .key_left = KEY_B,
                .key_right = KEY_R,
                .key_shoot = KEY_SPACE,
                .key_validate = KEY_ENTER,
                .key_cancel = KEY_DELETE,
                .key_settings = KEY_TAB
            }
        );

        _entities[2] = _coordinator->createEntity();
        _coordinator->addComponent(
            _entities[2],
            ECS::Model {
                .model = std::make_shared<RL::ZModel>("./client/resources/models/duck.obj"),
                .texture = std::make_shared<RL::ZTexture>("./client/resources/models/duck_text.png"),
            }
        );
        _coordinator->addComponent(
            _entities[2],
            ECS::Transform {
                .position = {0, 0, 0},
                .rotation = {0, 0, 0, 0},
                .scale = 0.1f
            }
        );
        _coordinator->addComponent(
            _entities[2],
            ECS::Player {
                .key_up = KEY_Y,
                .key_down = KEY_G,
                .key_left = KEY_B,
                .key_right = KEY_R,
                .key_shoot = KEY_SPACE,
                .key_validate = KEY_ENTER,
                .key_cancel = KEY_DELETE,
                .key_settings = KEY_TAB
            }
        );
    }

    void Core::initComponents() {
        _coordinator->init();

        _coordinator->registerComponent<ECS::Transform>();
        _coordinator->registerComponent<ECS::Model>();
        _coordinator->registerComponent<ECS::Player>();
    }

    void Core::initSystem() {
        _systems._systemMove = _coordinator->registerSystem<ECS::Move>();
        _systems._systemDrawModel = _coordinator->registerSystem<ECS::DrawModel>();
        _systems._systemPlayer = _coordinator->registerSystem<ECS::Play>();

        ECS::Signature signature;
        signature.set(_coordinator->getComponentType<ECS::Transform>());
        _coordinator->setSystemSignature<ECS::Move>(signature);

        ECS::Signature signature2;
        signature2.set(_coordinator->getComponentType<ECS::Transform>());
        signature2.set(_coordinator->getComponentType<ECS::Model>());
        signature2.set(_coordinator->getComponentType<ECS::Player>());
        _coordinator->setSystemSignature<ECS::DrawModel>(signature2);

        ECS::Signature signature3;
        signature3.set(_coordinator->getComponentType<ECS::Transform>());
        signature3.set(_coordinator->getComponentType<ECS::Model>());
        signature3.set(_coordinator->getComponentType<ECS::Player>());
        _coordinator->setSystemSignature<ECS::Play>(signature3);
    }

    void Core::loop() {
        initComponents();
        initSystem();
        initEntities();
        while (!_window->shouldClose()) {
            if (_cursor->isHidden())
                _camera->update(CAMERA_FIRST_PERSON);
            _window->beginDrawing();
            _window->clearBackground(RAYWHITE);
            _camera->beginMode();

            _systems._systemDrawModel->update();
            _systems._systemMove->update();
            _systems._systemPlayer->update(_event);

            _window->drawGrid(10, 1.0f);
            _camera->endMode();
            _window->drawFPS(10, 10);
            _window->endDrawing();

        }
    }
};
