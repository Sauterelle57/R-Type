/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** AudioStream.hpp
*/

#ifndef ZAPPY_GUI_AUDIOSTREAM_HPP
#define ZAPPY_GUI_AUDIOSTREAM_HPP

#include "IAudioStream.hpp"
#include <iostream>
#include <memory>
#include "raylib.h"

namespace ZappyGui {

    class ZAudioStream : public IAudioStream {
        public:
            ZAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels) {
                _audioStream = std::make_unique<AudioStream>(LoadAudioStream(sampleRate, sampleSize, channels));
            };

            ~ZAudioStream() {
                UnloadAudioStream(*_audioStream);
            };

            bool isReady() {
                return IsAudioStreamReady(*_audioStream);
            };

            void update(const void *data, int frameCount) {
                return UpdateAudioStream(*_audioStream, data, frameCount);
            };

            bool isProcessed() {
                return IsAudioStreamProcessed(*_audioStream);
            };

            void play() {
                return PlayAudioStream(*_audioStream);
            };

            void pause() {
                return PauseAudioStream(*_audioStream);
            };

            void resume() {
                return ResumeAudioStream(*_audioStream);
            };

            bool isPlaying() {
                return IsAudioStreamPlaying(*_audioStream);
            };

            void stop() {
                return StopAudioStream(*_audioStream);
            };

            void setVolume(float volume) {
                return SetAudioStreamVolume(*_audioStream, volume);
            };

            void setPitch(float pitch) {
                return SetAudioStreamPitch(*_audioStream, pitch);
            };

            void setPan(float pan) {
                return SetAudioStreamPan(*_audioStream, pan);
            };

            void setBufferSizeDefault(int size) {
                return SetAudioStreamBufferSizeDefault( size);
            };

            void setCallback(AudioCallback callback) {
                return SetAudioStreamCallback(*_audioStream, callback);
            };

            void attachProcessor(AudioCallback processor) {
                return AttachAudioStreamProcessor(*_audioStream, processor);
            };

            void detachProcessor(AudioCallback processor) {
                return DetachAudioStreamProcessor(*_audioStream, processor);
            };

            void attachAudioMixedProcessor(AudioCallback processor) {
                return AttachAudioMixedProcessor(processor);
            };

            void detachAudioMixedProcessor(AudioCallback processor) {
                return DetachAudioMixedProcessor(processor);
            };

            std::unique_ptr<AudioStream> _audioStream;
    };

} // ZappyGui

#endif //ZAPPY_GUI_AUDIOSTREAM_HPP
