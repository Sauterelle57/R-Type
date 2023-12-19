/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Sound.hpp
*/

#ifndef raylib_SOUND_HPP
#define raylib_SOUND_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "ISound.hpp"

namespace RL {

    class ZSound : public ISound {
        public:
            ZSound(const std::string &fileName) {
                _sound = std::make_unique<Sound>(LoadSound(fileName.c_str()));
            };

            ZSound(Wave wave) {
                _sound = std::make_unique<Sound>(LoadSoundFromWave(wave));
            };

            ~ZSound() {
                UnloadSound(*_sound);
            };

            bool isSoundReady() {
                return IsSoundReady(*_sound);
            };

            void updateSound(const void *data, int sampleCount) {
                return UpdateSound(*_sound, data, sampleCount);
            };

            void playSound() {
                return PlaySound(*_sound);
            };

            void stopSound() {
                return StopSound(*_sound);
            };

            void pauseSound() {
                return PauseSound(*_sound);
            };

            void resumeSound() {
                return ResumeSound(*_sound);
            };

            bool isSoundPlaying() {
                return IsSoundPlaying(*_sound);
            };

            void setSoundVolume(float volume) {
                return SetSoundVolume(*_sound, volume);
            };

            void setSoundPitch(float pitch) {
                return SetSoundPitch(*_sound, pitch);
            };

            void setSoundPan(float pan) {
                return SetSoundPan(*_sound, pan);
            };

            std::unique_ptr<Sound> _sound;
    };

} // RL

#endif //raylib_SOUND_HPP
