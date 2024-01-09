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

#include "ServerController.hpp"
#include "GameController.hpp"

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Received Ctrl+C. Stopping server..." << std::endl;
        exit(0);
    }
}

int main() {
    std::signal(SIGINT, signalHandler);
    std::shared_ptr<rt::IGameController> gameCtrl = std::make_shared<rt::GameController>();
    std::shared_ptr<rt::IServerController> serverCtrl = std::make_shared<rt::ServerController>(1234, gameCtrl);

    gameCtrl->addWrapper(serverCtrl->getWrapper());

    std::thread gameThread([&]() {
        gameCtrl->exec();
    });

    serverCtrl->run();
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
