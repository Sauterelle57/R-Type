/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IGameController
*/

#ifndef IGAMECONTROLLER_HPP_
#define IGAMECONTROLLER_HPP_
#include "IWrapper.hpp"
#include <map>
#include <memory>

namespace rt {

    struct ReceivedData {
        std::string data;
        std::string ip;
        int port;
    };

    struct SendData {
        std::string data;
        std::string ip;
        int port;
    };

    class IGameController {
        public:
            virtual ~IGameController() = default;
            virtual int exec() = 0;
            virtual void addReceivedData(const std::string &data, const std::string &ip, const int port) = 0;

            virtual void addWrapper(std::shared_ptr<IWrapper> wrapper) = 0;
    };

}

#endif /* !IGAMECONTROLLER_HPP_ */
