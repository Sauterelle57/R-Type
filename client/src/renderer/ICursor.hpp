/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** ICursor.hpp
*/

#ifndef raylib_ICURSOR_HPP
#define raylib_ICURSOR_HPP

struct Vector2;

namespace RL {
    class ICursor {
        public:
            virtual ~ICursor() = default;
            virtual void show() = 0;
            virtual void hide() = 0;
            virtual bool isHidden() = 0;
            virtual void enable() = 0;
            virtual void disable() = 0;
            virtual bool isOnScreen() = 0;
            virtual int getMouseX() = 0;
            virtual int getMouseY() = 0;
            virtual Vector2 getMousePosition() = 0;
            virtual Vector2 getMouseDelta() = 0;
            virtual void setMousePosition(int x, int y) = 0;
            virtual void setMouseOffset(int offsetX, int offsetY) = 0;
            virtual void setMouseScale(float scaleX, float scaleY) = 0;
            virtual float getMouseWheelMove() = 0;
            virtual Vector2 getMouseWheelMoveV() = 0;
            virtual void setMouseCursor(int cursor) = 0;
};

} // RL

#endif //raylib_ICURSOR_HPP
