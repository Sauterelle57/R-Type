/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Mode.hpp
*/

#ifndef ZAPPY_GUI_MODE_HPP
#define ZAPPY_GUI_MODE_HPP

#include <raylib.h>
#include <iostream>

#include "IMode.hpp"

namespace ZappyGui {

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

} // ZappyGui

#endif //ZAPPY_GUI_MODE_HPP
