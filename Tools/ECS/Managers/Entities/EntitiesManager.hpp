/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntitiesManager
*/

#ifndef ENTITIESMANAGER_HPP_
#define ENTITIESMANAGER_HPP_

#include <cstdint>
#include <queue>
#include <array>
#include "Entity.hpp"
#include "Error.hpp"

using Entity = std::uint32_t;

namespace ECS {
    class EntityManager {
        public:
            EntityManager() {
                for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                    _availableEntities.push(entity);
                }
            }

            Entity createEntity() {
//                if (_livingEntityCount >= MAX_ENTITIES)
//                    throw tls::Error("Too many entities.");
                Entity id = _availableEntities.front();
                _availableEntities.pop();
                _livingEntityCount++;
                return id;
            }

            void destroyEntity(Entity entity) {
//                if (_signatures[entity].any())
//                    throw tls::Error("Cannot destroy entity.");
                _signatures[entity].reset();
                _availableEntities.push(entity);
                _livingEntityCount--;
            }

            void setSignature(Entity entity, Signature signature) {
//                if (_signatures[entity].any())
//                    throw tls::Error("Signature already exists.");
                _signatures[entity] = signature;
            }

            Signature getSignature(Entity entity) {
//                if (_signatures[entity].none())
//                    throw tls::Error("Signature does not exist.");
                return _signatures[entity];
            }

        private:
            std::queue<Entity> _availableEntities{};
            std::array<Signature, MAX_ENTITIES> _signatures{};
            uint32_t _livingEntityCount{};
    };
}

#endif /* !ENTITIESMANAGER_HPP_ */
