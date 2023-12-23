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
#include "Traveling.hpp"
#include "Clock.hpp"
#include "ClientController.hpp"
#include "Shoot.hpp"
#include "Projectile.hpp"
#include "Collider.hpp"

namespace rt {

    class GameController : public IGameController {
        public:
            GameController();
            ~GameController() = default;

            int exec();

            void addReceivedData(const std::string &data, const std::string &ip, const int port);

            void addWrapper(IWrapper &wrapper);

            void commandHandler(const std::string &data, const std::string &ip, const int port);

            void command_ping(const std::string &data, const std::string &ip, const int port);
            void command_move(const std::string &data, const std::string &ip, const int port);
            void command_shoot(const std::string &data, const std::string &ip, const int port);
            void command_request_connection(const std::string &data, const std::string &ip, const int port);

            struct System {
                std::shared_ptr<ECS::TravelingSystem> _systemTraveling;
                std::shared_ptr<ECS::ProjectileSystem> _systemProjectile;
                std::shared_ptr<ECS::Shoot> _systemShoot;
                std::shared_ptr<ECS::ColliderSystem> _systemCollider;
            };
        private:
            int i = 0;
            std::queue<ReceivedData> _receivedData;
            IWrapper *_wrapper;
            std::map<std::string, std::function<void(const std::string &, const std::string &, const int)>> _commands;

            void _initializeCommands();
            void _initializeECS();
            void _initializeECSComponents();
            void _initializeECSSystems();
            void _initializeECSEntities();

            ECS::Entity _createPlayer();
            ECS::Entity _createEnnemy();
            ECS::Entity _createTile();
            ECS::Entity _createBreakableTile();
            void _eventController();
            void _eventController_transform(std::shared_ptr<Client> client);
            void _eventController_camera();
            void _eventController_ennemy();
            void _eventController_tile();
            void _eventController_breakable_tile();
            
            rt::ClientController _clientController;

            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::set<ECS::Entity> _entities;
            std::map<ECS::Entity, bool> _entitiesShoot;
            bool _cameraInit;
            ECS::Entity _camera;
            ECS::Entity _ennemy;
            ECS::Entity _tile;
            ECS::Entity _breakableTile;

            System _systems;
            tls::Clock _clock;
    };

}

#endif /* !GAMECONTROLLER_HPP_ */
