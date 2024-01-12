//
// Created by noahg on 10/01/2024.
//

#ifndef RTYPE_MUSIC_HPP
#define RTYPE_MUSIC_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class MusicSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &music = coordinatorPtr->getComponent<Music>(entity);

                    if (!music.music->isReady())
                        continue;
                    if (!music.music->isPlaying()) {
                        music.music->play();
                    }
                    music.music->update();

                }
            }
    };
}

#endif //RTYPE_MUSIC_HPP
