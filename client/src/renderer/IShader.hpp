/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IShader.hpp
*/

#ifndef raylib_ISHADER_HPP
#define raylib_ISHADER_HPP

#include <iostream>
#include <memory>

struct Matrix;
struct Texture;

namespace RL {

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

} // RL

#endif //raylib_ISHADER_HPP
