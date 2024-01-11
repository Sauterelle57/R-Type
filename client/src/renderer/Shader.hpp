/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Shader.hpp
*/

#ifndef raylib_SHADER_HPP
#define raylib_SHADER_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IShader.hpp"

namespace RL {

    class ZShader : public IShader {
        public:
            ZShader(const std::string &vsFileName, const std::string &fsFileName) {
                _shader = std::make_unique<Shader>(LoadShader(vsFileName.c_str(), fsFileName.c_str()));
            };
            ZShader(const std::string &fsFileName) {
                _shader = std::make_unique<Shader>(LoadShader(0, fsFileName.c_str()));
            };
            ~ZShader() {
                UnloadShader(*_shader);
            };

            static Shader load(const std::string &vsFileName, const std::string &fsFileName) {
                return LoadShader(vsFileName.c_str(), fsFileName.c_str());
            };

            bool isReady() {
                return IsShaderReady(*_shader);
            };

            int getLocation(const std::string &uniformName) {
                return GetShaderLocation(*_shader, uniformName.c_str());
            };

            static int getLocation(Shader shader, const std::string &uniformName) {
                return GetShaderLocation(shader, uniformName.c_str());
            };

            static int getLocationAttrib(Shader shader, const std::string &attribName) {
                return GetShaderLocationAttrib(shader, attribName.c_str());
            };

            int getLocationAttrib(const std::string &attribName) {
                return GetShaderLocationAttrib(*_shader, attribName.c_str());
            };

            void setValue(int locIndex, const void *value, int uniformType) {
                return SetShaderValue(*_shader, locIndex, value, uniformType);
            };

            static void setValue(Shader shader, int locIndex, const void *value, int uniformType) {
                return SetShaderValue(shader, locIndex, value, uniformType);
            };

            void setValueV(int locIndex, const void *value, int uniformType, int count) {
                return SetShaderValueV(*_shader, locIndex, value, uniformType, count);
            };

            void setValueMatrix(int locIndex, Matrix mat) {
                return SetShaderValueMatrix(*_shader, locIndex, mat);
            };

            void setValueTexture(int locIndex, Texture2D texture) {
                return SetShaderValueTexture(*_shader, locIndex, texture);
            };

            void beginMode() {
                return BeginShaderMode(*_shader);
            };

            void endMode() {
                return EndShaderMode();
            };

            std::unique_ptr<Shader> &getShader() {
                return _shader;
            };

            std::unique_ptr<Shader> _shader;

    };

} // RL

#endif //raylib_SHADER_HPP
