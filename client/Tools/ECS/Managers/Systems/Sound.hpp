/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Sound.hpp
*/

#ifndef RTYPE_SOUND_HPP
#define RTYPE_SOUND_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class SoundSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &sound = coordinatorPtr->getComponent<Sound>(entity);

                    if (!sound.alreadyPlayed || sound.loop) {
                        sound.sound->playSound();
                        sound.alreadyPlayed = true;
                    }
                }
            }
    };
}

#endif //RTYPE_SOUND_HPP
