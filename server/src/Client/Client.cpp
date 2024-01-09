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
