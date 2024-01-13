/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IRenderTexture.hpp
*/

#ifndef raylib_IRENDERTEXTURE_HPP
#define raylib_IRENDERTEXTURE_HPP

namespace RL {

    class IRenderTexture {
        public:
            virtual ~IRenderTexture() = default;
            virtual bool isReady() = 0;
            virtual void draw(int posX, int posY, Color tint) = 0;
            virtual void endMode() = 0;
            virtual void beginMode() = 0;
    };

} // RL

#endif //raylib_IRENDERTEXTURE_HPP
