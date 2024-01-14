
/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntitiesManager
*/

#ifndef ENTITIESMANAGER_HPP_
#define ENTITIESMANAGER_HPP_

#include <queue>
#include <array>
#include "Error.hpp"
#include "IEntitiesManager.hpp"

using Entity = std::uint32_t;

namespace ECS {
    class EntityManager : public IEntityManager {
        public:
            EntityManager() {
                for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                    _availableEntities.push(entity);
                }
            }

            Entity createEntity() {
                if (_livingEntityCount >= MAX_ENTITIES)
                    throw tls::Error("Too many entities.");
                Entity id = _availableEntities.front();
                _availableEntities.pop();
                _livingEntityCount++;
                return id;
            }

            void destroyEntity(Entity entity) {
                if (entity > MAX_ENTITIES || entity < 0)
                    throw tls::Error("Cannot destroy entity.");
                _signatures[entity].reset();
                _availableEntities.push(entity);
                _livingEntityCount--;
            }

            void setSignature(Entity entity, Signature signature) {
                if (entity > MAX_ENTITIES || entity < 0)
                    throw tls::Error("Cannot set signature.");
                _signatures[entity] = signature;
            }

            Signature getSignature(Entity entity) {
                if (entity > MAX_ENTITIES || entity < 0)
                    throw tls::Error("Cannot get signature.");
                return _signatures[entity];
            }

            uint32_t getLivingEntityCount() const {
                return _livingEntityCount;
            }

        private:
            std::queue<Entity> _availableEntities{};
            std::array<Signature, MAX_ENTITIES> _signatures{};
            uint32_t _livingEntityCount{};
    };
}

#endif /* !ENTITIESMANAGER_HPP_ */
