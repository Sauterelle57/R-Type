/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Audio.hpp
*/

#ifndef ZAPPY_GUI_AUDIO_HPP
#define ZAPPY_GUI_AUDIO_HPP

#include <iostream>
#include <raylib.h>
#include "IAudio.hpp"

namespace ZappyGui {

    class ZAudio : public IAudio {
        public:
            ZAudio() {
                InitAudioDevice();
            };
            ~ZAudio() {
                CloseAudioDevice();
            };

            bool isDeviceReady() {
                return IsAudioDeviceReady();
            };

            void setMasterVolume(float volume) {
                return SetMasterVolume(volume);
            };
    };

} // ZappyGui

#endif //ZAPPY_GUI_AUDIO_HPP
