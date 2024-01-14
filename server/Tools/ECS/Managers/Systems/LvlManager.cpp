/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LvlManager.cpp
*/

#include "LvlManager.hpp"
#include "GameController.hpp"

void ECS::LvlManager::update(rt::GameController &gameController) {
    auto coordinatorPtr = _coordinator.lock();
    if (!coordinatorPtr) {
        return;
    }

    auto &camera = coordinatorPtr->getComponent<ECS::Transform>(gameController._camera);

    for (auto const &entity : _entities) {
        auto &level = coordinatorPtr->getComponent<Level>(entity);


        for (const auto& step : level.data.step) {
            if (level.alreadyReached.contains(step.pos_x) || step.pos_x > camera.position._x)
                continue;

            for (const auto& entity : step.entity) {
                if (entity.type == "enemy1") {
                    gameController._createEnemy({entity.x + camera.position._x, entity.y, entity.z}, entity.shootSpeed);
                }
                if (entity.type == "boss") {
                    gameController._createBoss({entity.x + camera.position._x, entity.y, entity.z}, entity.shootSpeed, 20);
                }
            }
            level.alreadyReached.insert(step.pos_x);
        }
    }
}