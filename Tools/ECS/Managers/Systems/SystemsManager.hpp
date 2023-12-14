/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemsManager
*/

#ifndef SYSTEMSMANAGER_HPP_
#define SYSTEMSMANAGER_HPP_

#include <memory>
#include <unordered_map>
#include "../Entities/Entity.hpp"
#include "../../../Error/Error.hpp"
#include "System.hpp"

namespace ECS {
    class Coordinator;
    class SystemManager {
        public:
            SystemManager(std::weak_ptr<Coordinator> &coordinator) : _coordinator(coordinator) {};
            ~SystemManager() = default;
            template<typename T>
            std::shared_ptr<T> registerSystem() {
                const char *typeName = typeid(T).name();

//                if (_systems.find(typeName) != _systems.end())
//                    throw tls::Error("Registering system more than once.");

                auto system = std::make_shared<T>(_coordinator);
                _systems.insert({typeName, system});
                return system;
            }

            template<typename T>
            void setSignature(Signature signature) {
                const char *typeName = typeid(T).name();

//                if (_systems.find(typeName) == _systems.end())
//                    throw tls::Error("System used before registered.");

                _signatures.insert({typeName, signature});
            }

            void entityDestroyed(Entity entity) {
                for (auto const &pair: _systems) {
                    auto const &system = pair.second;

                    system->_entities.erase(entity);
                }
            }

            void entitySignatureChanged(Entity entity, Signature entitySignature) {
                for (auto const &pair: _systems) {
                    auto const &type = pair.first;
                    auto const &system = pair.second;
                    auto const &systemSignature = _signatures[type];

                    if ((entitySignature & systemSignature) == systemSignature) {
                        system->_entities.insert(entity);
                    }
                    else {
                        system->_entities.erase(entity);
                    }
                }
            }

        private:
            std::weak_ptr<Coordinator> _coordinator;
            std::unordered_map<const char *, Signature> _signatures{};
            std::unordered_map<const char *, std::shared_ptr<System>> _systems{};
    };
}

#endif /* !SYSTEMSMANAGER_HPP_ */
