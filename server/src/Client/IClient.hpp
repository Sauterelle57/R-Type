/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** ICLient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_
#include <iostream>
#include <string>

class IClient {
    public:
        virtual ~IClient() = default;

        virtual std::string getIpAdress() const = 0;
        virtual int getPort() const = 0;
};

#endif /* !ICLIENT_HPP_ */
