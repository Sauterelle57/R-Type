/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IModelAnimation.hpp
*/

#ifndef raylib_IMODELANIMATION_HPP
#define raylib_IMODELANIMATION_HPP

namespace RL {

    class IModelAnimation {
        public:
            virtual ~IModelAnimation() = default;
            virtual ModelAnimation *getModelAnimation() = 0;
        };

} // RL

#endif //raylib_IMODELANIMATION_HPP
