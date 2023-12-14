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
#include "Core.hpp"
#include "Utils.hpp"
#include "DrawModel.hpp"
#include "Move.hpp"

namespace RT {
    Core::Core()
    {
        _window = std::make_shared<RL::ZWindow>(_screenWidth, _screenHeight, "R TYPE test light");
        _camera = std::make_shared<RL::ZCamera>();
        _camera->setPosition((Vector3){ 25.0f, 20.0f, 6.0f });
        _camera->setTarget((Vector3){ 0.0f, 8.0f, 0.0f });
        _camera->setUp((Vector3){ 0.0f, 1.0f, 0.0f });
        _camera->setFovy(45.0f);
        _camera->setProjection(CAMERA_FIRST_PERSON);

        _cursor = std::make_shared<RL::ZCursor>();
        _cursor->disable();
        _event = std::make_shared<RL::ZEvent>();
        _event->setExitKey(KEY_F4);

        _coordinator = std::make_shared<ECS::Coordinator>();
        _coordinator->init();

        _coordinator->registerComponent<ECS::Transform>();
        _coordinator->registerComponent<ECS::Model>();

        SetTargetFPS(60);
    }

    void Core::initEntities() {
        _entities[0] = _coordinator->createEntity();
        _coordinator->addComponent(
            _entities[0],
            ECS::Transform {
                .position = {100, 0, 100},
                .rotation = {0, 0, 0, 0},
                .scale = {0, 0, 0}
            }
        );
        _entities[1] = _coordinator->createEntity();
        _coordinator->addComponent(
            _entities[1],
            ECS::Transform {{0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}}
        );
    }

    void Core::initComponents() {
        ECS::Signature signature;
        signature.set(_coordinator->getComponentType<ECS::Transform>());
        _coordinator->setSystemSignature<ECS::Move>(signature);

        ECS::Signature signature2;
        signature2.set(_coordinator->getComponentType<ECS::Transform>());
        signature2.set(_coordinator->getComponentType<ECS::DrawModel>());
        _coordinator->setSystemSignature<ECS::DrawModel>(signature2);

        _coordinator->addComponent(
            _entities[1],
            ECS::Model{
                .model = std::make_shared<RL::ZModel>("./client/resources/models/ship.glb")
            }
        );
    }

    void Core::initSystem() {
        _systems[0] = std::make_unique<ECS::System>(_coordinator->registerSystem<ECS::Move>());
        _systems[1] = std::make_unique<ECS::System>(_coordinator->registerSystem<ECS::DrawModel>());
    }

    void Core::loop() {
        initEntities();
        initComponents();
        while (!_window->shouldClose()) {
            if (_cursor->isHidden())
                _camera->update(CAMERA_FIRST_PERSON);

            _window->beginDrawing();
            _window->clearBackground(RAYWHITE);
            _camera->beginMode();

            int32_t entityCount = _coordinator->getLivingEntityCount();
            int32_t count = 0;

            for (auto const &system : _systems) {
                system->update();
            }
        }
    }
};
