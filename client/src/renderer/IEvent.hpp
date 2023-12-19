/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IEvent.hpp
*/

#ifndef raylib_IEVENT_HPP
#define raylib_IEVENT_HPP

#include <iostream>

namespace RL {

    class IEvent {
        public:
            virtual ~IEvent() = default;
            virtual void enableWaiting() = 0;
            virtual void disableWaiting() = 0;
            virtual void pollInputEvents() = 0;
            virtual bool isKeyPressed(int key) = 0;
            virtual bool isKeyDown(int key) = 0;
            virtual bool isKeyReleased(int key) = 0;
            virtual bool isKeyUp(int key) = 0;
            virtual void setExitKey(int key) = 0;
            virtual int getKeyPressed() = 0;
            virtual int getCharPressed() = 0;
            virtual bool isGamepadAvailable(int gamepad) = 0;
            virtual std::string getGamepadName(int gamepad) = 0;
            virtual bool isGamepadButtonPressed(int gamepad, int button) = 0;
            virtual bool isGamepadButtonDown(int gamepad, int button) = 0;
            virtual bool isGamepadButtonReleased(int gamepad, int button) = 0;
            virtual bool isGamepadButtonUp(int gamepad, int button) = 0;
            virtual int getGamepadButtonPressed() = 0;
            virtual int getGamepadAxisCount(int gamepad) = 0;
            virtual float getGamepadAxisMovement(int gamepad, int axis) = 0;
            virtual int setGamepadMappings(const std::string &mappings) = 0;
            virtual bool isMouseButtonPressed(int button) = 0;
            virtual bool isMouseButtonDown(int button) = 0;
            virtual bool isMouseButtonReleased(int button) = 0;
            virtual bool isMouseButtonUp(int button) = 0;
            virtual int getTouchX() = 0;
            virtual int getTouchY() = 0;
    };

} // RL

#endif //raylib_IEVENT_HPP
