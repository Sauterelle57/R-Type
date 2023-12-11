//
// Created by noah on 12/11/23.
//

#ifndef RTYPE_COORDINATOR_HPP
#define RTYPE_COORDINATOR_HPP

#include <memory>
#include "ComponentsManager.hpp"
#include "EntitiesManager.hpp"
#include "SystemsManager.hpp"

namespace ECS {
    class Coordinator {
        public:
            void Init() {
                _componentManager = std::make_unique<ComponentManager>();
                _entityManager = std::make_unique<EntityManager>();
                _systemManager = std::make_unique<SystemManager>();
            }

            Entity CreateEntity() {
                return _entityManager->CreateEntity();
            }

            void DestroyEntity(Entity entity) {
                _entityManager->DestroyEntity(entity);
                _componentManager->EntityDestroyed(entity);
                _systemManager->EntityDestroyed(entity);
            }

            template<typename T>
            void RegisterComponent() {
                _componentManager->RegisterComponent<T>();
            }

            template<typename T>
            void AddComponent(Entity entity, T component) {
                _componentManager->AddComponent<T>(entity, component);

                auto signature = _entityManager->GetSignature(entity);
                signature.set(_componentManager->GetComponentType<T>(), true);
                _entityManager->SetSignature(entity, signature);

                _systemManager->EntitySignatureChanged(entity, signature);
            }

            template<typename T>
            void RemoveComponent(Entity entity) {
                _componentManager->RemoveComponent<T>(entity);

                auto signature = _entityManager->GetSignature(entity);
                signature.set(_componentManager->GetComponentType<T>(), false);
                _entityManager->SetSignature(entity, signature);

                _systemManager->EntitySignatureChanged(entity, signature);
            }

            template<typename T>
            T& GetComponent(Entity entity) {
                return _componentManager->GetComponent<T>(entity);
            }

            template<typename T>
            ComponentType GetComponentType() {
                return _componentManager->GetComponentType<T>();
            }

            template<typename T>
            std::shared_ptr<T> RegisterSystem() {
                return _systemManager->RegisterSystem<T>();
            }

            template<typename T>
            void SetSystemSignature(Signature signature) {
                _systemManager->SetSignature<T>(signature);
            }

        private:
            std::unique_ptr<ComponentManager> _componentManager;
            std::unique_ptr<EntityManager> _entityManager;
            std::unique_ptr<SystemManager> _systemManager;
    };
};

#endif //RTYPE_COORDINATOR_HPP
