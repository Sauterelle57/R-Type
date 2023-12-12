/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IShader.hpp
*/

#ifndef ZAPPY_GUI_ISHADER_HPP
#define ZAPPY_GUI_ISHADER_HPP

#include <iostream>
#include <memory>

struct Matrix;
struct Texture;

namespace ZappyGui {

    class IShader {
        public:
            virtual ~IShader() = default;
            virtual bool isReady() = 0;
            virtual int getLocation(const std::string &uniformName) = 0;
            virtual int getLocationAttrib(const std::string &attribName) = 0;
            virtual void setValue(int locIndex, const void *value, int uniformType) = 0;
            virtual void setValueV(int locIndex, const void *value, int uniformType, int count) = 0;
            virtual void setValueMatrix(int locIndex, Matrix mat) = 0;
            virtual void setValueTexture(int locIndex, Texture2D texture) = 0;
            virtual void beginMode() = 0;
            virtual void endMode() = 0;
            virtual std::unique_ptr<Shader> &getShader() = 0;
        };

} // ZappyGui

#endif //ZAPPY_GUI_ISHADER_HPP
