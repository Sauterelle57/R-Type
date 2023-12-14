/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include "Coordinator.hpp"
#include "renderer/IWindow.hpp"
#include "renderer/ICamera.hpp"
#include "renderer/ICursor.hpp"
#include "renderer/IEvent.hpp"
#include "renderer/IMusic.hpp"
#include "renderer/ISound.hpp"
#include "renderer/IAudio.hpp"
#include "Move.hpp"
#include "DrawModel.hpp"

namespace RT {

    struct System {
        std::shared_ptr<ECS::DrawModel> _systemDrawModel;
        std::shared_ptr<ECS::Move> _systemMove;
    };

    class Core {
        public:
            Core();
            ~Core() = default;
            void loop();
            void initEntities();
            void initComponents();
            void initSystem();
            const int _screenWidth = 1920;
            const int _screenHeight = 1080;

            std::shared_ptr<RL::IWindow> _window;
            std::shared_ptr<RL::ICamera> _camera;
            std::shared_ptr<RL::ICursor> _cursor;
            std::shared_ptr<RL::IEvent> _event;

            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::vector<ECS::Entity> _entities;
            System _systems;
    };
};

#endif /* !CORE_HPP_ */
