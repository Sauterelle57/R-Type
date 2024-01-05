//
// Created by noahg on 28/12/2023.
//

#ifndef RTYPE_SELFDESTRUCT_HPP
#define RTYPE_SELFDESTRUCT_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class SelfDestructSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &dest = coordinatorPtr->getComponent<SelfDestruct>(entity);

                    if (dest.timer.isTimeElapsed()) {
                        coordinatorPtr->destroyEntity(entity);
                        return;
                    }
                }
            }
    };
}

#endif //RTYPE_SELFDESTRUCT_HPP
