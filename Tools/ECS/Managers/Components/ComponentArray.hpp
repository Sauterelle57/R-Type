//
// Created by noah on 12/11/23.
//

#ifndef RTYPE_COMPONENTARRAY_HPP
#define RTYPE_COMPONENTARRAY_HPP

#include <unordered_map>
#include "Entity.hpp"
#include "error.hpp"

namespace ECS {

    class IComponentArray {
        public:
            virtual ~IComponentArray() = default;
            virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
        public:
            void InsertData(Entity entity, T component) {
                if (_entityToIndexMap.find(entity) != _entityToIndexMap.end())
                    throw tls::Error("Component added to same entity more than once.");
                size_t newIndex = _size;
                _entityToIndexMap[entity] = newIndex;
                _indexToEntityMap[newIndex] = entity;
                _componentArray[newIndex] = component;
                _size++;
            }

            void RemoveData(Entity entity) {
                if (_entityToIndexMap.find(entity) == _entityToIndexMap.end())
                    throw tls::Error("Removing non-existent component.");
                size_t indexOfRemovedEntity = _entityToIndexMap[entity];
                size_t indexOfLastElement = _size - 1;
                _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

                Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
                _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
                _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

                _entityToIndexMap.erase(entity);
                _indexToEntityMap.erase(indexOfLastElement);

                _size--;
            }

            T& GetData(Entity entity) {
                if (_entityToIndexMap.find(entity) == _entityToIndexMap.end())
                    throw tls::Error("Retrieving non-existent component.");

                return _componentArray[_entityToIndexMap[entity]];
            }

            void EntityDestroyed(Entity entity) override {
                if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
                    RemoveData(entity);
                }
            }

        private:
            std::array<T, MAX_ENTITIES> _componentArray{};
            std::unordered_map<Entity, size_t> _entityToIndexMap{};
            std::unordered_map<size_t, Entity> _indexToEntityMap{};

            size_t _size{};
    };
}

#endif //RTYPE_COMPONENTARRAY_HPP
