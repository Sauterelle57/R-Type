/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** main.cpp
*/

#include <iostream>

#include "ServerController.hpp"
#include "GameController.hpp"

int main() {
    std::unique_ptr<rt::IServerController> serverCtrl = std::make_unique<rt::ServerController>(1234);

    serverCtrl->run();

    return 0;
}
