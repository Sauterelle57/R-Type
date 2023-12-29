/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Coordinator
*/

#ifndef RTYPE_COORDINATOR_HPP
#define RTYPE_COORDINATOR_HPP

#include <memory>
#include "EntitiesManager.hpp"
#include "ComponentsManager.hpp"
#include "SystemsManager.hpp"

namespace ECS {
    class Coordinator : public std::enable_shared_from_this<Coordinator>{
        public:
            Coordinator() = default;
            ~Coordinator() = default;

            void init() {
                _componentManager = std::make_unique<ComponentManager>();
                _entityManager = std::make_unique<EntityManager>();
                std::weak_ptr<Coordinator> weakThis = shared_from_this();
                _systemManager = std::make_unique<SystemManager>(weakThis);
            }

            Entity createEntity() {
                return _entityManager->createEntity();
            }

            void destroyEntity(Entity entity) {
                _entityManager->destroyEntity(entity);
                _componentManager->entityDestroyed(entity);
                _systemManager->entityDestroyed(entity);
            }

            uint32_t getLivingEntityCount() {
                return _entityManager->getLivingEntityCount();
            }

            template<typename T>
            void registerComponent() {
                _componentManager->registerComponent<T>();
            }

            template<typename T>
            void addComponent(Entity entity, T component) {
                _componentManager->addComponent<T>(entity, component);

                auto signature = _entityManager->getSignature(entity);
                signature.set(_componentManager->getComponentType<T>(), true);
                _entityManager->setSignature(entity, signature);

                _systemManager->entitySignatureChanged(entity, signature);
            }

            template<typename T>
            void removeComponent(Entity entity) {
                _componentManager->removeComponent<T>(entity);

                auto signature = _entityManager->getSignature(entity);
                signature.set(_componentManager->getComponentType<T>(), false);
                _entityManager->setSignature(entity, signature);

                _systemManager->entitySignatureChanged(entity, signature);
            }

            template<typename T>
            T& getComponent(Entity entity) {
                return _componentManager->getComponent<T>(entity);
            }

            template<typename T>
            ComponentType getComponentType() {
                return _componentManager->getComponentType<T>();
            }

            template<typename T>
            std::shared_ptr<T> registerSystem() {
                return _systemManager->registerSystem<T>();
            }

            template<typename T>
            void setSystemSignature(Signature signature) {
                _systemManager->setSignature<T>(signature);
            }

        private:
            std::unique_ptr<ComponentManager> _componentManager;
            std::unique_ptr<EntityManager> _entityManager;
            std::unique_ptr<SystemManager> _systemManager;
    };
};

#endif //RTYPE_COORDINATOR_HPP
