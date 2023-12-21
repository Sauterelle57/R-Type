/*
** EPITECH PROJECT, 2023
** Client.cpp
** File description:
** Client
*/

#include "Client.hpp"

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
