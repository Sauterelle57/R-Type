//
// Created by noah on 12/20/23.
//

#ifndef RTYPE_CAM_HPP
#define RTYPE_CAM_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include "MultipleLink.hpp"

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
                    auto player = MultipleLinkManager::getTo(coordinatorPtr, entity, "target");
                    camera.camera->setPosition(transform.position);
                    if (player != -1) {
                        auto &playerTransform = coordinatorPtr->getComponent<Transform>(player);
                        camera.camera->setTarget(playerTransform.position);
                    } else {
                        camera.camera->setTarget(camera.camera->getPosition() + tls::Vec3{0, 0, -1});
                    }
//                    std::cout << "Position: " << camera.camera->getPosition()._x << " " << camera.camera->getPosition()._y << " " << camera.camera->getPosition()._z << std::endl;
//                    std::cout << "Target: " << camera.camera->getTarget().x << " " << camera.camera->getTarget().y << " " << camera.camera->getTarget().z << std::endl;
                }
            }
    };
}

#endif //RTYPE_CAM_HPP
