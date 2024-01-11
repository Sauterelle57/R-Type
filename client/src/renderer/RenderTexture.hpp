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
    class ZRenderTexture2D : public IRenderTexture {
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

            void beginMode() {
                return BeginTextureMode(*_target.get());
            };

            void endMode() {
                return EndTextureMode();
            };

            void draw(int posX, int posY, Color tint) {
                return DrawTextureRec(_target->texture, {0, 0, static_cast<float>(_target->texture.width), static_cast<float>(-_target->texture.height)}, {static_cast<float>(posX), static_cast<float>(posY)}, tint);
            };

            std::unique_ptr<RenderTexture2D> _target;
    };

} // RL

#endif //raylib_RENDERTEXTURE_HPP
