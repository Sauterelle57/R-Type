/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Camera2D.hpp
*/

#ifndef ZAPPY_GUI_CAMERA2D_HPP
#define ZAPPY_GUI_CAMERA2D_HPP

#include <iostream>
#include <raylib.h>
#include <memory>
#include "ICamera2D.hpp"

namespace ZappyGui {

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

} // ZappyGui

#endif //ZAPPY_GUI_CAMERA2D_HPP
