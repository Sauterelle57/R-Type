//
// Created by noah on 12/20/23.
//

#ifndef RTYPE_CAM_HPP
#define RTYPE_CAM_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class CamSystem : public System {
        public:
            void begin() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &camera = coordinatorPtr->getComponent<Cam>(entity);

                    camera.camera->beginMode();
                }
            }
            void end() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &camera = coordinatorPtr->getComponent<Cam>(entity);

                    camera.camera->endMode();
                }
            }

            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &camera = coordinatorPtr->getComponent<Cam>(entity);
                    camera.camera->setTarget(transform.position + tls::Vec3{0, 0, -10});

                    camera.camera->setPosition(transform.position);
                }
            }
    };
}

#endif //RTYPE_CAM_HPP
