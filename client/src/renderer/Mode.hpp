/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Mode.hpp
*/

#ifndef raylib_MODE_HPP
#define raylib_MODE_HPP

#include <raylib.h>
#include <iostream>

#include "IMode.hpp"

namespace RL {

    class ZMode : public IMode {
        public:
            void beginTexture(RenderTexture2D target) {
                return BeginTextureMode(target);
            };

            void endTexture() {
                return EndTextureMode();
            };

            void beginBlend(int mode) {
                return BeginBlendMode(mode);
            };

            void endBlend() {
                return EndBlendMode();
            };

            void beginScissor(int x, int y, int width, int height) {
                return BeginScissorMode(x, y, width, height);
            };

            void endScissor() {
                return EndScissorMode();
            };

            void beginVrStereo(VrStereoConfig config) {
                return BeginVrStereoMode(config);
            };

            void endVrStereo() {
                return EndVrStereoMode();
            };

    };

} // RL

#endif //raylib_MODE_HPP
