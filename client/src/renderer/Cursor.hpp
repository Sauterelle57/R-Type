/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Cursor.hpp
*/

#ifndef raylib_CURSOR_HPP
#define raylib_CURSOR_HPP

#include <raylib.h>
#include "ICursor.hpp"

namespace RL {

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

} // RL

#endif //raylib_CURSOR_HPP
