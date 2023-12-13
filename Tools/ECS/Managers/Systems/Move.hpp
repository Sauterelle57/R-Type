//
// Created by noah on 12/12/23.
//

#ifndef RTYPE_MOVE_HPP
#define RTYPE_MOVE_HPP

#include "System.hpp"

namespace ECS {
    class Move : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    transform.position._y -= 0.1;
                    if (transform.position._y < 0) {
                        transform.position._y = 20;
                    }
                }
            }
    };
}


#endif //RTYPE_MOVE_HPP
