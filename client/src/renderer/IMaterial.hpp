/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IMaterial.hpp
*/

#ifndef ZAPPY_GUI_IMATERIAL_HPP
#define ZAPPY_GUI_IMATERIAL_HPP

#include <iostream>

#include <memory>

struct Texture;

namespace ZappyGui {

    class IMaterial {
        public:
            virtual ~IMaterial() = default;
            virtual bool isReady() = 0;
            virtual void setTexture(int mapType, Texture2D texture) = 0;
            virtual std::unique_ptr<Material> &getMaterial() = 0;
            };

} // ZappyGui

#endif //ZAPPY_GUI_IMATERIAL_HPP
