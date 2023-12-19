/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IMusic.hpp
*/

#ifndef raylib_IMUSIC_HPP
#define raylib_IMUSIC_HPP

namespace RL {

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

} // RL

#endif //raylib_IMUSIC_HPP
