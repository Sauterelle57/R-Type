/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ComponentsManager
*/

#ifndef COMPONENTSMANAGER_HPP_
#define COMPONENTSMANAGER_HPP_

#include <memory>
#include "ComponentArray.hpp"

namespace ECS {
    class ComponentManager {
        public:
            template<typename T>
            void RegisterComponent() {
                const char* typeName = typeid(T).name();
                if (_componentTypes.find(typeName) != _componentTypes.end())
                    throw tls::Error("Registering component more than once.");
                _componentTypes.insert({typeName, _nextComponentType});
                _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
                _nextComponentType++;
            }

            template<typename T>
            ComponentType GetComponentType() {
                const char* typeName = typeid(T).name();

                if (_componentTypes.find(typeName) == _componentTypes.end())
                    throw tls::Error("Component used before registered.");
                return _componentTypes[typeName];
            }

            template<typename T>
            void AddComponent(Entity entity, T component) {
                GetComponentArray<T>()->InsertData(entity, component);
            }

            template<typename T>
            void RemoveComponent(Entity entity) {
                GetComponentArray<T>()->RemoveData(entity);
            }

            template<typename T>
            T& GetComponent(Entity entity) {
                return GetComponentArray<T>()->GetData(entity);
            }

            void EntityDestroyed(Entity entity) {
                for (auto const& pair : _componentArrays) {
                    auto const& component = pair.second;
                    component->EntityDestroyed(entity);
                }
            }

        private:
            std::unordered_map<const char*, ComponentType> _componentTypes{};
            std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays{};
            ComponentType _nextComponentType{};

            template<typename T>
            std::shared_ptr<ComponentArray<T>> GetComponentArray() {
                const char* typeName = typeid(T).name();

                if (_componentTypes.find(typeName) == _componentTypes.end())
                    throw tls::Error("Component used before registered.");
                return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
            }
    };
}

#endif /* !COMPONENTSMANAGER_HPP_ */
