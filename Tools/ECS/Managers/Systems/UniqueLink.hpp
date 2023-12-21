/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** UniqueLink.hpp
*/

#ifndef RTYPE_UNIQUELINK_HPP
#define RTYPE_UNIQUELINK_HPP

#include "ComponentStructs.hpp"
#include "Coordinator.hpp"

namespace ECS {
    class UniqueLinkManager {
        public:
            static void createLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;
                coordinatorPtr->addComponent(
                    entityA,
                    UniqueLink{
                        .to = entityB
                    }
                );
                coordinatorPtr->addComponent(
                    entityB,
                    UniqueLink{
                        .from = entityA
                    }
                );
            }
            static void modifyLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;
                auto &linkA = coordinatorPtr->getComponent<UniqueLink>(entityA);
                auto &linkB = coordinatorPtr->getComponent<UniqueLink>(entityB);
                linkA.to = entityB;
                linkB.from = entityA;
            }
    };
}

#endif //RTYPE_UNIQUELINK_HPP
