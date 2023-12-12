/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IMode.hpp
*/

#ifndef ZAPPY_GUI_IMODE_HPP
#define ZAPPY_GUI_IMODE_HPP

struct RenderTexture;
struct VrStereoConfig;

namespace ZappyGui {

    class IMode {
        public:
            virtual ~IMode() = default;
            virtual void beginTexture(RenderTexture2D target) = 0;
            virtual void endTexture() = 0;
            virtual void beginBlend(int mode) = 0;
            virtual void endBlend() = 0;
            virtual void beginScissor(int x, int y, int width, int height) = 0;
            virtual void endScissor() = 0;
            virtual void beginVrStereo(VrStereoConfig config) = 0;
            virtual void endVrStereo() = 0;
    };

} // ZappyGui

#endif //ZAPPY_GUI_IMODE_HPP
