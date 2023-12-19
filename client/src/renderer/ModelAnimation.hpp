/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** ModelAnimation.hpp
*/

#ifndef raylib_MODELANIMATION_HPP
#define raylib_MODELANIMATION_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IModelAnimation.hpp"

namespace RL {

    class ZModelAnimation : public IModelAnimation {
        public:
            ZModelAnimation(const std::string &fileName, int *animCount) {
                _modelAnimation = LoadModelAnimations(fileName.c_str(), animCount);
            };

            ~ZModelAnimation() {
                UnloadModelAnimation(*_modelAnimation);
            };

            ModelAnimation *getModelAnimation() {
                return _modelAnimation;
            };

            ModelAnimation *_modelAnimation;

    };

} // RL

#endif //raylib_MODELANIMATION_HPP
