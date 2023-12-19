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

        private:
            int i = 0;
            std::queue<ReceivedData> _receivedData;
            IWrapper *_wrapper;
            std::map<std::string, std::function<void(const std::string &, const std::string &, const int)>> _commands;

            void _initializeCommands();

    };

}

#endif /* !GAMECONTROLLER_HPP_ */
