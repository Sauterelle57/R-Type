/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** MultipleLink.hpp
*/

#ifndef RTYPE_MULTIPLELINK_HPP
#define RTYPE_MULTIPLELINK_HPP

#include "ComponentStructs.hpp"
#include "Coordinator.hpp"

namespace ECS {
    class MultipleLinkManager {
        public:
            static void createLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;
                coordinatorPtr->addComponent(
                        entityA,
                        MultipleLink{
                            .to = std::set<Entity>{entityB}
                        }
                );
                coordinatorPtr->addComponent(
                        entityB,
                        MultipleLink{
                            .from = std::set<Entity>{entityA}
                        }
                );
            }
            static void addLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;
                auto &linkA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                auto &linkB = coordinatorPtr->getComponent<MultipleLink>(entityB);
                linkA.to.insert(entityB);
                linkB.from.insert(entityA);
            }
            static void removeLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;
                auto &linkA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                auto &linkB = coordinatorPtr->getComponent<MultipleLink>(entityB);
                linkA.to.erase(entityB);
                linkB.from.erase(entityA);
            }
    };
}

#endif //RTYPE_MULTIPLELINK_HPP
