/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_
#include "IClient.hpp"
#include <iostream>
#include <string>
#include <map>

namespace rt
{
    class Client : public IClient {
        public:
            Client(std::string ipAdress, int port);
            ~Client();
            std::string getIpAdress() const;
            int getPort() const;
            void setPlayerID(const int id);
            int getPlayerID() const;
        private:
            std::string _ipAdress;
            int _port;
            int _playerID;
            std::map<EventType, bool> _events;
    };
}

#endif /* !CLIENT_HPP_ */
