/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IMode.hpp
*/

#ifndef raylib_IMODE_HPP
#define raylib_IMODE_HPP

struct RenderTexture;
struct VrStereoConfig;

namespace RL {

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

} // RL

#endif //raylib_IMODE_HPP
