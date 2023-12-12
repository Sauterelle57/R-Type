/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IAudioStream.hpp
*/

#ifndef ZAPPY_GUI_IAUDIOSTREAM_HPP
#define ZAPPY_GUI_IAUDIOSTREAM_HPP

typedef void (*AudioCallback)(void *bufferData, unsigned int frames);

namespace ZappyGui {

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

} // ZappyGui

#endif //ZAPPY_GUI_IAUDIOSTREAM_HPP
