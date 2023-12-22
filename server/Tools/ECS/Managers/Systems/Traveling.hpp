//
// Created by noah on 12/20/23.
//

#ifndef RTYPE_TRAVELING_HPP
#define RTYPE_TRAVELING_HPP


#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class TravelingSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &traveling = coordinatorPtr->getComponent<Traveling>(entity);

                    //std::cout << transform.position._x << std::endl;

                    transform.position += traveling.speed;
                }
            }
    };
}

#endif //RTYPE_TRAVELING_HPP
