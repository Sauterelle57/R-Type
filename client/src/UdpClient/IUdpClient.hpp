/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IUdpClient
*/

#ifndef IUDP_CLIENT_HPP_
#define IUDP_CLIENT_HPP_

#include <string>

class IUdpClient {
public:
    virtual ~IUdpClient() = default;

    virtual void send(const std::string& message) = 0;
    virtual void receive() = 0;
};

#endif // IUDP_CLIENT_HPP_
