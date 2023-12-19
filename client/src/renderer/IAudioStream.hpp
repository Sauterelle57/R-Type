/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IAudioStream.hpp
*/

#ifndef raylib_IAUDIOSTREAM_HPP
#define raylib_IAUDIOSTREAM_HPP

typedef void (*AudioCallback)(void *bufferData, unsigned int frames);

namespace RL {

    class IAudioStream {
        public:
            virtual ~IAudioStream() = default;
            virtual bool isReady() = 0;
            virtual void update(const void *data, int frameCount) = 0;
            virtual bool isProcessed() = 0;
            virtual void play() = 0;
            virtual void pause() = 0;
            virtual void resume() = 0;
            virtual bool isPlaying() = 0;
            virtual void stop() = 0;
            virtual void setVolume(float volume) = 0;
            virtual void setPitch(float pitch) = 0;
            virtual void setPan(float pan) = 0;
            virtual void setBufferSizeDefault(int size) = 0;
            virtual void setCallback(AudioCallback callback) = 0;
            virtual void attachProcessor(AudioCallback processor) = 0;
            virtual void detachProcessor(AudioCallback processor) = 0;
            virtual void attachAudioMixedProcessor(AudioCallback processor) = 0;
            virtual void detachAudioMixedProcessor(AudioCallback processor) = 0;
    };

} // RL

#endif //raylib_IAUDIOSTREAM_HPP
