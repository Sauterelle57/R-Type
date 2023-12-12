/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Music.hpp
*/

#ifndef ZAPPY_GUI_MUSIC_HPP
#define ZAPPY_GUI_MUSIC_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IMusic.hpp"

namespace ZappyGui {

    class ZMusic : public IMusic {
        public:
            ZMusic(const std::string &fileName) {
                _music = std::make_unique<Music>(LoadMusicStream(fileName.c_str()));
            };

            ~ZMusic() {
                UnloadMusicStream(*_music);
            };

            bool isReady() {
                return IsMusicReady(*_music);
            };

            void play() {
                return PlayMusicStream(*_music);
            };

            bool isPlaying() {
                return IsMusicStreamPlaying(*_music);
            };

            void update() {
                return UpdateMusicStream(*_music);
            };

            void stop() {
                return StopMusicStream(*_music);
            };

            void pause() {
                return PauseMusicStream(*_music);
            };

            void resume() {
                return ResumeMusicStream(*_music);
            };

            void seek(float position) {
                return SeekMusicStream(*_music, position);
            };

            void setVolume(float volume) {
                return SetMusicVolume(*_music, volume);
            };

            void setPitch(float pitch) {
                return SetMusicPitch(*_music, pitch);
            };

            void setPan(float pan) {
                return SetMusicPan(*_music, pan);
            };

            float getTimeLength() {
                return GetMusicTimeLength(*_music);
            };

            float getTimePlayed() {
                return GetMusicTimePlayed(*_music);
            };

            std::unique_ptr<Music> _music;
    };

} // ZappyGui

#endif //ZAPPY_GUI_MUSIC_HPP
