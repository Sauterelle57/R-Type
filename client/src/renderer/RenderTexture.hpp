/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** RenderTexture.hpp
*/

#ifndef ZAPPY_GUI_RENDERTEXTURE_HPP
#define ZAPPY_GUI_RENDERTEXTURE_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IRenderTexture.hpp"

namespace ZappyGui {
    class ZRenderTexture2D : IRenderTexture {
        public:
            ZRenderTexture2D(int width, int height) {
                _target = std::make_unique<RenderTexture2D>(LoadRenderTexture(width, height));
            };

            ~ZRenderTexture2D() {
                UnloadRenderTexture(*_target);
            };

            bool isReady() {
                return IsRenderTextureReady(*_target);
            };

            std::unique_ptr<RenderTexture2D> _target;
    };

} // ZappyGui

#endif //ZAPPY_GUI_RENDERTEXTURE_HPP
