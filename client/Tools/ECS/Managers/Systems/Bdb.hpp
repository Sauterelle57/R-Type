//
// Created by noahg on 09/01/2024.
//

#ifndef RTYPE_BDB_HPP
#define RTYPE_BDB_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include "renderer/Utils.hpp"

namespace ECS {
    class BdbSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &bdb = coordinatorPtr->getComponent<Bdb>(entity);

                    RL::Utils::drawBoundingBox(bdb.bounds, RED);
                }
            }
    };
}

#endif //RTYPE_BDB_HPP
