/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_
#include "IClient.hpp"

class Client : public IClient {
    public:
        Client(std::string ipAdress, int port);
        ~Client();
        std::string getIpAdress() const;
        int getPort() const;
    private:
        std::string _ipAdress;
        int _port;
};

#endif /* !CLIENT_HPP_ */
