/*
** EPITECH PROJECT, 2023
** Client.cpp
** File description:
** Client
*/

#include "Client.hpp"

namespace rt
{
    Client::Client(std::string ipAdress, int port)
    {
        _ipAdress = ipAdress;
        _port = port;
        _deltaMgr = std::make_shared<DeltaManager>();
    }

    Client::~Client()
    {
    }

    std::string Client::getIpAdress() const
    {
        return _ipAdress;
    }

    int Client::getPort() const
    {
        return _port;
    }

    std::shared_ptr<DeltaManager> Client::getDeltaManager()
    {
        return _deltaMgr;
    }

//    void Client::setPlayerID(const int id)
//    {
//        _playerID = id;
//    }
//
//    int Client::getPlayerID() const
//    {
//        return _playerID;
//    }
}
