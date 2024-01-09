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
    return 0;
}