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
    };

} // RL

#endif //raylib_IRENDERTEXTURE_HPP
