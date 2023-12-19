/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IAudio.hpp
*/

#ifndef raylib_IAUDIO_HPP
#define raylib_IAUDIO_HPP

namespace RL {

    class IAudio {
        public:
            virtual ~IAudio() = default;

            virtual bool isDeviceReady() = 0;

            virtual void setMasterVolume(float volume) = 0;
    };

} // RL

#endif //raylib_IAUDIO_HPP
