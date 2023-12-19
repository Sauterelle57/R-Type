/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** ISound.hpp
*/

#ifndef raylib_ISOUND_HPP
#define raylib_ISOUND_HPP

namespace RL {

    class ISound {
        public:
            virtual ~ISound() = default;
            virtual bool isSoundReady() = 0;
            virtual void updateSound(const void *data, int sampleCount) = 0;
            virtual void playSound() = 0;
            virtual void stopSound() = 0;
            virtual void pauseSound() = 0;
            virtual void resumeSound() = 0;
            virtual bool isSoundPlaying() = 0;
            virtual void setSoundVolume(float volume) = 0;
            virtual void setSoundPitch(float pitch) = 0;
            virtual void setSoundPan(float pan) = 0;
    };

} // RL

#endif //raylib_ISOUND_HPP
