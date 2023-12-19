/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Audio.hpp
*/

#ifndef raylib_AUDIO_HPP
#define raylib_AUDIO_HPP

#include <iostream>
#include <raylib.h>
#include "IAudio.hpp"

namespace RL {

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

} // RL

#endif //raylib_AUDIO_HPP
