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
    std::unique_ptr<rt::ServerController> serverCtrl = std::make_unique<rt::ServerController>(1234);

    serverCtrl->run();
    std::cout << "Server ended" << std::endl;

    return 0;
}
