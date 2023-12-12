/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IMusic.hpp
*/

#ifndef ZAPPY_GUI_IMUSIC_HPP
#define ZAPPY_GUI_IMUSIC_HPP

namespace ZappyGui {

    class IMusic {
        public:
            virtual ~IMusic() = default;
            virtual bool isReady() = 0;
            virtual void play() = 0;
            virtual bool isPlaying() = 0;
            virtual void update() = 0;
            virtual void stop() = 0;
            virtual void pause() = 0;
            virtual void resume() = 0;
            virtual void seek(float position) = 0;
            virtual void setVolume(float volume) = 0;
            virtual void setPitch(float pitch) = 0;
            virtual void setPan(float pan) = 0;
            virtual float getTimeLength() = 0;
            virtual float getTimePlayed() = 0;
    };

} // ZappyGui

#endif //ZAPPY_GUI_IMUSIC_HPP
