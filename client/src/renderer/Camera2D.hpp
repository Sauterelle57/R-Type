/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Camera2D.hpp
*/

#ifndef raylib_CAMERA2D_HPP
#define raylib_CAMERA2D_HPP

#include <iostream>
#include <raylib.h>
#include <memory>
#include "ICamera2D.hpp"

namespace RL {

    class ZCamera2D : public ICamera2D {
        public:
            ZCamera2D() {
                _camera = std::make_unique<Camera2D>();
            };
            ~ZCamera2D() = default;

            Matrix getMatrix2D() const {
                return GetCameraMatrix2D(*_camera);
            };

            void beginMode() {
                return BeginMode2D(*_camera);
            };

            void endMode() {
                return EndMode2D();
            };

            std::unique_ptr<Camera2D> _camera;
    };

} // RL

#endif //raylib_CAMERA2D_HPP
