/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** DrawModel
*/

#ifndef RTYPE_DRAWMODEL_HPP
#define RTYPE_DRAWMODEL_HPP

#include "System.hpp"
#include "Coordinator.hpp"

namespace ECS {
    class DrawModel : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                int32_t entityCount = coordinatorPtr->getLivingEntityCount();
                int32_t count = 0;
                for (auto const &entity : _entities) {
                    if (count++ >= entityCount) {
                        return;
                    }
                    auto &model = coordinatorPtr->getComponent<Model>(entity);

                    model.model->draw(coordinatorPtr->getComponent<Transform>(entity).position, 1.0f, WHITE);
                }
            }
    };
}

#endif //RTYPE_DRAWMODEL_HPP
