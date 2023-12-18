/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Main
*/

#include "UdpClient.hpp"

int main()
{
    boost::asio::io_service ioService;

    rt::UdpClient udpClient("127.0.0.1", 1234);

    udpClient.send("ABC");
    udpClient.send("DEF123");

    udpClient.receive();

    udpClient.receive();

    udpClient.send("Here is a message");
    return 0;
}
