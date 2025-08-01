/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <mutex>
#include <thread>
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
#include "Play.hpp"
#include "Particle.hpp"
#include "Cam.hpp"
#include "Traveling.hpp"
#include "IListener.hpp"
#include "IUdpClient.hpp"
#include "UdpClient.hpp"
#include "Sound.hpp"
#include "SelfDestruct.hpp"
#include "Lights.hpp"
#include "ShaderUpdater.hpp"
#include "ModelAnimation.hpp"
#include "Velocity.hpp"
#include "Bdb.hpp"
#include "Music.hpp"
#include "Modal.hpp"

namespace RT {

    struct System {
        std::shared_ptr<ECS::Move> _systemMove;
        std::shared_ptr<ECS::Play> _systemPlayer;
        std::shared_ptr<ECS::DrawModel> _systemDrawModel;
        std::shared_ptr<ECS::ParticleSystem> _systemParticles;
        std::shared_ptr<ECS::CamSystem> _systemCamera;
        std::shared_ptr<ECS::TravelingSystem> _systemTraveling;
        std::shared_ptr<ECS::SoundSystem> _systemSound;
        std::shared_ptr<ECS::SelfDestructSystem> _systemSelfDestruct;
        std::shared_ptr<ECS::LightSystem> _systemLight;
        std::shared_ptr<ECS::ShaderUpdaterSystem> _systemShaderUpdater;
        std::shared_ptr<ECS::VelocitySystem> _systemVelocity;
        std::shared_ptr<ECS::BdbSystem> _systemBdb;
        std::shared_ptr<ECS::MusicSystem> _systemMusic;
        std::shared_ptr<ECS::ModalSystem> _systemModal;
        std::shared_ptr<ECS::ModelAnimationSystem> _systemAnimation;
    };

    class Core {
        public:
            Core();
            ~Core();
            void loop();
            void initEntities();
            void initComponents();
            void initSystem();
            void checkCollision(ECS::Entity entity1, ECS::Entity entity2);
            const int _screenWidth = 1920;
            const int _screenHeight = 1080;

            std::shared_ptr<RL::IWindow> _window;
            std::shared_ptr<RL::ICamera> _camera;
            std::shared_ptr<RL::ICursor> _cursor;
            std::shared_ptr<RL::IEvent> _event;

            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::shared_ptr<std::set<ECS::Entity>> _entities;
            System _systems;

            std::unique_ptr<IListener> _listener;

            std::shared_ptr<std::queue<rt::ReceivedMessage>> _receivedMessages;
            std::shared_ptr<rt::UdpClient> _udpClient;
            std::unique_ptr<std::thread> _udpClientThread;

            std::shared_ptr<bool> _isRunning;

            std::unique_ptr<tls::IClock> _clock;

            std::unique_ptr<RL::IAudio> _audio;

            std::shared_ptr<std::mutex> _messageQueueMutex;
            std::shared_ptr<std::mutex> _isRunningMutex;

            bool _shouldClose = false;
            bool _debug = false;
    };
};

#endif /* !CORE_HPP_ */
