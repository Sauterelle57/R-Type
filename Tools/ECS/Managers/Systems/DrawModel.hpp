//
// Created by noah on 12/13/23.
//

#ifndef RTYPE_DRAWMODEL_HPP
#define RTYPE_DRAWMODEL_HPP

#include "System.hpp"

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
