//
// Created by noahg on 01/01/2024.
//

#ifndef RTYPE_MODELANIMATION_HPP
#define RTYPE_MODELANIMATION_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class ModelAnimationSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &animation = coordinatorPtr->getComponent<Animation>(entity);
                    auto &model = coordinatorPtr->getComponent<Model>(entity);

                    ModelAnimation anim = animation.modelAnimation->getModelAnimation()[animation.animIndex];
                    animation.animCurrentFrame = (animation.animCurrentFrame + 1) % anim.frameCount;
                    model.model->updateAnimation(anim, animation.animCurrentFrame);
                }
            }
    };
}

#endif //RTYPE_MODELANIMATION_HPP
