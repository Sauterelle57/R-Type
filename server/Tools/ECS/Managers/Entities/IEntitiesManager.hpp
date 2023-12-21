//
// Created by noah on 12/19/23.
//

#ifndef RTYPE_IENTITIESMANAGER_HPP
#define RTYPE_IENTITIESMANAGER_HPP

#include <cstdint>
#include "Entity.hpp"

namespace ECS {
    class IEntityManager {
        public:
            virtual ~IEntityManager() = default;

            virtual Entity createEntity() = 0;
            virtual void destroyEntity(Entity entity) = 0;
            virtual void setSignature(Entity entity, Signature signature) = 0;
            virtual Signature getSignature(Entity entity) = 0;
            virtual uint32_t getLivingEntityCount() const = 0;
    };
}

#endif //RTYPE_IENTITIESMANAGER_HPP
