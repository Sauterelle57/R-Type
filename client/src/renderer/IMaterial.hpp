/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IMaterial.hpp
*/

#ifndef raylib_IMATERIAL_HPP
#define raylib_IMATERIAL_HPP

#include <iostream>

#include <memory>

struct Texture;

namespace RL {

    class IMaterial {
        public:
            virtual ~IMaterial() = default;
            virtual bool isReady() = 0;
            virtual void setTexture(int mapType, Texture2D texture) = 0;
            virtual std::unique_ptr<Material> &getMaterial() = 0;
            };

} // RL

#endif //raylib_IMATERIAL_HPP
