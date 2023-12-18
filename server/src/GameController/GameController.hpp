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
            GameController() = default;
            ~GameController() = default;
            int exec() { 
                while (1) {
                    std::cout << "GameController" << std::endl;
                    // get data from queue
                    if (!_receivedData.empty()) {
                        ReceivedData data = _receivedData.front();
                        _receivedData.pop();
                        std::cout << "GameController exec data: " << data.data << " from " << data.ip << ":" << data.port << std::endl;
                        _wrapper->sendTo(data.data, data.ip, data.port);
                    }
                }
            }

            void addReceivedData(const std::string &data, const std::string &ip, const int port) {
                std::cout << "GameController received data: " << data << " from " << ip << ":" << port << std::endl;
                _receivedData.push({data, ip, port});
            }

            void addWrapper(IWrapper &wrapper) {
                std::cout << "GameController addWrapper" << std::endl;
                _wrapper = &wrapper;
            }
        private:
            int i = 0;
            std::queue<ReceivedData> _receivedData;
            IWrapper *_wrapper;

    };

}

#endif /* !GAMECONTROLLER_HPP_ */
