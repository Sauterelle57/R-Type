/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** GameController
*/

#ifndef GAMECONTROLLER_HPP_
#define GAMECONTROLLER_HPP_
#include "IGameController.hpp"
#include <iostream>
#include <queue>
#include <functional>
#include "Coordinator.hpp"

#include "Utils.hpp"
#include "Move.hpp"
#include "AutoMove.hpp"
#include "Traveling.hpp"
#include "Clock.hpp"
#include "ClientController.hpp"
#include "Shoot.hpp"
#include "Projectile.hpp"
#include "Collider.hpp"
#include "ClientUpdater.hpp"
#include "PlayerManager.hpp"
#include "ParentManager.hpp"

namespace rt {

    class GameController : public IGameController {
        public:
            GameController();
            ~GameController() = default;

            int exec();

            void addReceivedData(const std::string &data, const std::string &ip, const int port);

            void addWrapper(std::shared_ptr<IWrapper> wrapper);

            void commandHandler(const std::string &data, const std::string &ip, const int port);

            void commandPing(const std::string &data, const std::string &ip, const int port);
            void commandMove(const std::string &data, const std::string &ip, const int port);
            void commandShoot(const std::string &data, const std::string &ip, const int port);
            void commandRequestConnection(const std::string &data, const std::string &ip, const int port);
            void commandID(const std::string &data, const std::string &ip, const int port);

            struct System {
                std::shared_ptr<ECS::TravelingSystem> _systemTraveling;
                std::shared_ptr<ECS::ProjectileSystem> _systemProjectile;
                std::shared_ptr<ECS::Shoot> _systemShoot;
                std::shared_ptr<ECS::ColliderSystem> _systemCollider;
                std::shared_ptr<ECS::ClientUpdaterSystem> _systemClientUpdater;
                std::shared_ptr<ECS::PlayerManager> _systemPlayerManager;
                std::shared_ptr<ECS::ParentManager> _systemParent;
                std::shared_ptr<ECS::Move> _systemMove;
                std::shared_ptr<ECS::AutoMove> _systemAutoMove;
            };
        private:
            int i = 0;
            std::queue<ReceivedData> _receivedData;
            std::shared_ptr<IWrapper> _wrapper;
            std::shared_ptr<rt::ClientController> _clientController;

            std::map<std::string, std::function<void(const std::string &, const std::string &, const int)>> _commands;

            void _initializeCommands();
            void _initializeECS();
            void _initializeECSComponents();
            void _initializeECSSystems();
            void _initializeECSEntities();

            void _createPlayer(std::string ip, int port);
            void _createEnemy(tls::Vec3 pos, float clockSpeed);
            void _createBoss(tls::Vec3 pos, float clockSpeed, int nbChildren);
            void _createChild(ECS::Entity parent, float offset, bool armed);
            void _createTile(tls::Vec3 pos);
            void _createBreakableTile(tls::Vec3 pos);

            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::set<ECS::Entity> _entities;
            bool _cameraInit;
            ECS::Entity _camera;

            System _systems;
            tls::Clock _clock;
            tls::Clock _clockBossChild;
            tls::Clock _clockEnemySpawn;
            int _waveEnemy;

            std::shared_ptr<ProtocolController> _pc;
    };

}

#endif /* !GAMECONTROLLER_HPP_ */
