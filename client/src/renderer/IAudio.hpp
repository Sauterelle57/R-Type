/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IAudio.hpp
*/

#ifndef ZAPPY_GUI_IAUDIO_HPP
#define ZAPPY_GUI_IAUDIO_HPP

namespace ZappyGui {

    class IAudio {
        public:
            virtual ~IAudio() = default;

            virtual bool isDeviceReady() = 0;

            virtual void setMasterVolume(float volume) = 0;
    };

} // ZappyGui

#endif //ZAPPY_GUI_IAUDIO_HPP
