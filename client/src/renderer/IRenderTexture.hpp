/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IRenderTexture.hpp
*/

#ifndef ZAPPY_GUI_IRENDERTEXTURE_HPP
#define ZAPPY_GUI_IRENDERTEXTURE_HPP

namespace ZappyGui {

    class IRenderTexture {
        public:
            virtual ~IRenderTexture() = default;
            virtual bool isReady() = 0;
    };

} // ZappyGui

#endif //ZAPPY_GUI_IRENDERTEXTURE_HPP
