/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** ModelAnimation.hpp
*/

#ifndef ZAPPY_GUI_MODELANIMATION_HPP
#define ZAPPY_GUI_MODELANIMATION_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IModelAnimation.hpp"

namespace ZappyGui {

    class ZModelAnimation : public IModelAnimation {
        public:
            ZModelAnimation(const std::string &fileName, unsigned int *animCount) {
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

} // ZappyGui

#endif //ZAPPY_GUI_MODELANIMATION_HPP
