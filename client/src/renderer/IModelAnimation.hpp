/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IModelAnimation.hpp
*/

#ifndef ZAPPY_GUI_IMODELANIMATION_HPP
#define ZAPPY_GUI_IMODELANIMATION_HPP

namespace ZappyGui {

    class IModelAnimation {
        public:
            virtual ~IModelAnimation() = default;
            virtual ModelAnimation *getModelAnimation() = 0;
        };

} // ZappyGui

#endif //ZAPPY_GUI_IMODELANIMATION_HPP
