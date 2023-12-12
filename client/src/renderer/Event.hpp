/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Event.hpp
*/

#ifndef ZAPPY_GUI_EVENT_HPP
#define ZAPPY_GUI_EVENT_HPP

#include <raylib.h>
#include "IEvent.hpp"
#include <iostream>

namespace ZappyGui {

    class ZEvent : public IEvent {
        public:
            void enableWaiting() {
                return EnableEventWaiting();
            };

            void disableWaiting() {
                return DisableEventWaiting();
            };

            void pollInputEvents() {
                return PollInputEvents();
            };

            bool isKeyPressed(int key) {
                return IsKeyPressed(key);
            };

            bool isKeyDown(int key) {
                return IsKeyDown(key);
            };

            bool isKeyReleased(int key) {
                return IsKeyReleased(key);
            };

            bool isKeyUp(int key) {
                return IsKeyUp(key);
            };

            void setExitKey(int key) {
                return SetExitKey(key);
            };

            int getKeyPressed() {
                return GetKeyPressed();
            };

            int getCharPressed() {
                return GetCharPressed();
            };

            bool isGamepadAvailable(int gamepad) {
                return IsGamepadAvailable(gamepad);
            };

            std::string getGamepadName(int gamepad) {
                return GetGamepadName(gamepad);
            };

            bool isGamepadButtonPressed(int gamepad, int button) {
                return IsGamepadButtonPressed(gamepad, button);
            };

            bool isGamepadButtonDown(int gamepad, int button) {
                return IsGamepadButtonDown(gamepad, button);
            };

            bool isGamepadButtonReleased(int gamepad, int button) {
                return IsGamepadButtonReleased(gamepad, button);
            };

            bool isGamepadButtonUp(int gamepad, int button) {
                return IsGamepadButtonUp(gamepad, button);
            };

            int getGamepadButtonPressed() {
                return GetGamepadButtonPressed();
            };

            int getGamepadAxisCount(int gamepad) {
                return GetGamepadAxisCount(gamepad);
            };

            float getGamepadAxisMovement(int gamepad, int axis) {
                return GetGamepadAxisMovement(gamepad, axis);
            };

            int setGamepadMappings(const std::string &mappings) {
                return SetGamepadMappings(mappings.c_str());
            };

            bool isMouseButtonPressed(int button) {
                return IsMouseButtonPressed(button);
            };

            bool isMouseButtonDown(int button) {
                return IsMouseButtonDown(button);
            };

            bool isMouseButtonReleased(int button) {
                return IsMouseButtonReleased(button);
            };

            bool isMouseButtonUp(int button) {
                return IsMouseButtonUp(button);
            };

            int getTouchX() {
                return GetTouchX();
            };

            int getTouchY() {
                return GetTouchY();
            };
    };

} // ZappyGui

#endif //ZAPPY_GUI_EVENT_HPP
