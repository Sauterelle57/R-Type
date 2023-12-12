/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Cursor.hpp
*/

#ifndef ZAPPY_GUI_CURSOR_HPP
#define ZAPPY_GUI_CURSOR_HPP

#include <raylib.h>
#include "ICursor.hpp"

namespace ZappyGui {

    class ZCursor : public ICursor {
        public:
            ZCursor() = default;
            ~ZCursor() = default;

            void show() {
                return ShowCursor();
            };

            void hide() {
                return HideCursor();
            };

            bool isHidden() {
                return IsCursorHidden();
            };

            void enable() {
                return EnableCursor();
            };

            void disable() {
                return DisableCursor();
            };

            bool isOnScreen() {
                return IsCursorOnScreen();
            };
            int getMouseX() {
                return GetMouseX();
            };

            int getMouseY() {
                return GetMouseY();
            };

            Vector2 getMousePosition() {
                return GetMousePosition();
            };

            Vector2 getMouseDelta() {
                return GetMouseDelta();
            };

            void setMousePosition(int x, int y) {
                return SetMousePosition(x, y);
            };

            void setMouseOffset(int offsetX, int offsetY) {
                return SetMouseOffset(offsetX, offsetY);
            };

            void setMouseScale(float scaleX, float scaleY) {
                return SetMouseScale(scaleX, scaleY);
            };

            float getMouseWheelMove() {
                return GetMouseWheelMove();
            };

            Vector2 getMouseWheelMoveV() {
                return GetMouseWheelMoveV();
            };

            void setMouseCursor(int cursor) {
                return SetMouseCursor(cursor);
            };

    };

} // ZappyGui

#endif //ZAPPY_GUI_CURSOR_HPP
