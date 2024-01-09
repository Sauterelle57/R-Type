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
#include <set>

namespace ECS {
    class MultipleLinkManager {
        public:
            static void createLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB, std::string name) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;

                coordinatorPtr->addComponent<MultipleLink>(entityA, MultipleLink{});
                coordinatorPtr->addComponent<MultipleLink>(entityB, MultipleLink{});
                auto &multiA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                auto &multiB = coordinatorPtr->getComponent<MultipleLink>(entityB);
                multiA.links.insert(UniqueLink{
                    .name = name,
                    .to = entityB
                });
                multiB.links.insert({
                    .name = name,
                    .from = entityB
                });
            }

            static void removeLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;

                auto &multiA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                auto &multiB = coordinatorPtr->getComponent<MultipleLink>(entityB);
                multiA.links.erase({
                    .to = entityB
                });
                multiB.links.erase({
                    .from = entityB
                });
            }

            static void removeLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, const std::string &name) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;

                auto &multiA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                for (auto it = multiA.links.begin(); it != multiA.links.end(); it++) {
                    if (it->name == name) {
                        auto &multiB = coordinatorPtr->getComponent<MultipleLink>(it->to);
                        multiB.links.erase({
                            .from = entityA
                        });
                        multiA.links.erase(it);
                        break;
                    }
                }
            }

            static void changeLink(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, Entity entityB, const std::string &name) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return;

                auto &multiA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                auto &multiB = coordinatorPtr->getComponent<MultipleLink>(entityB);

                removeLink(coordinator, entityA, name);
                createLink(coordinator, entityA, entityB, name);
            }

            static Entity getTo(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, const std::string &name) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return -1;

                auto &multiA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                for (const auto &link : multiA.links) {
                    if (link.name == name) {
                        return link.to;
                    }
                }
                return -1;
            }

            static Entity getFrom(const std::weak_ptr<Coordinator> &coordinator, Entity entityA, const std::string &name) {
                auto coordinatorPtr = coordinator.lock();
                if (!coordinatorPtr)
                    return -1;

                auto &multiA = coordinatorPtr->getComponent<MultipleLink>(entityA);
                for (const auto &link : multiA.links) {
                    if (link.name == name) {
                        return link.from;
                    }
                }
                return -1;
            }
    };
}

#endif //RTYPE_MULTIPLELINK_HPP
