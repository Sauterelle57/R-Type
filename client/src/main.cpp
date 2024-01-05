/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Main
*/

#include "UdpClient.hpp"
#include <thread>
#include <csignal>
#include "Core.hpp"

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Received Ctrl+C. Stopping client..." << std::endl;
        exit(0);
    }
}

int main()
{
    try {
        std::signal(SIGINT, signalHandler);
        std::unique_ptr<RT::Core> core = std::make_unique<RT::Core>();
        core->loop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

//    std::shared_ptr<std::queue<rt::ReceivedMessage>> receivedMessages = std::make_shared<std::queue<rt::ReceivedMessage>>();
//    rt::UdpClient udpClient;
//
//    udpClient.setup("127.0.0.1", 1234, receivedMessages);
//
//    std::thread udpClientThread([&]() {
//        udpClient.run();
//    });
//
//    while (1) {
//        while (!receivedMessages->empty())
//        {
//            std::cout << "Received message:" << std::endl;
//            std::cout << "Message: [" << receivedMessages->front().message << "]" << std::endl;
//            receivedMessages->pop();
//            std::cout << "-------------------" << std::endl;
//        }
//
//        std::cout << "GameLoop" << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        udpClient.send("PING");
//    }
//
//    udpClientThread.join();
    return 0;
}