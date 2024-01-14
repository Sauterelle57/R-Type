/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main
*/

#include <iostream>
#include <thread>
#include <memory>
#include <csignal>
#include <array>
#include <cstring>
#include <bitset>

#include "ServerController.hpp"
#include "GameController.hpp"
#include "Protocol.hpp"
#include "IServerController.hpp"
#include "ArgsManager.hpp"

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Received Ctrl+C. Stopping server..." << std::endl;
        exit(0);
    }
}


int main(int argc, char **argv) {
    try {
        std::signal(SIGINT, signalHandler);
        rt::ArgsManager argumentManager;
        bool debug = argumentManager.hasDebugFlag(argc, argv);
        std::shared_ptr<rt::IGameController> gameCtrl = std::make_shared<rt::GameController>(debug);
        std::optional<int> argServerPort = argumentManager.getServerPort(argc, argv);
        int serverPort = (argServerPort.has_value()) ? argServerPort.value() : 1234;

        if (argumentManager.hasHelpFlag(argc, argv)) {
            std::cout << "Rtype Server" << std::endl;
            std::cout << "-h, --help\t:\t Help Menu" << std::endl;
            std::cout << "-p PORT\t\t:\t Custom running port" << std::endl;
            std::cout << "-d, --debug\t:\t Debug mode" << std::endl;
            return 0;
        }
        if (serverPort <= 0 && serverPort <= 65000) {
            std::cerr << "Error: Please enter a valid port" << std::endl;
            return 84;
        }
        std::cout << "Running server on : " << serverPort << std::endl;
        
        std::shared_ptr<rt::IServerController> serverCtrl = std::make_shared<rt::ServerController>(serverPort, gameCtrl, debug);

        gameCtrl->addWrapper(serverCtrl->getWrapper());

        std::thread gameThread([&]() {
            gameCtrl->exec();
        });

        serverCtrl->run();
    } catch (...) {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Rtype Server - An error occured." << std::endl;
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Please check that the port is not already in use." << std::endl;
    }
    return 0;
}



//#include "collisions.hpp"


//int main() {
//    BoundingBox bbox1 = loadModelAndGetBoundingBox("./client/resources/models/player.glb");
//    BoundingBox bbox2 = loadModelAndGetBoundingBox("./client/resources/models/player.glb");
//
//    // Appliquer des transformations (exemple)
//    Vector3 position1 = {0, 0, 0}, scale1 = {1, 1, 1};
//    Vector3 position2 = {10, 0, 0}, scale2 = {1, 1, 1};
//    BoundingBox transformedBbox1 = bbox1.transform(position1, scale1);
//    BoundingBox transformedBbox2 = bbox2.transform(position2, scale2);
//
//    // Vérifier la collision
//    if (transformedBbox1.intersects(transformedBbox2)) {
//        std::cout << "Collision detected." << std::endl;
//    } else {
//        std::cout << "No collision." << std::endl;
//    }
//
//    return 0;
//}
