/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** RenderTexture.hpp
*/

#ifndef raylib_RENDERTEXTURE_HPP
#define raylib_RENDERTEXTURE_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IRenderTexture.hpp"

namespace RL {
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

} // RL

#endif //raylib_RENDERTEXTURE_HPP
