/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IWave.hpp
*/

#ifndef raylib_IWAVE_HPP
#define raylib_IWAVE_HPP

#include <iostream>

struct Wave;

namespace RL {

    class IWave {
        public:
            virtual ~IWave() = default;
            virtual bool isReady() = 0;
            virtual Wave copy() = 0;
            virtual void crop(int initSample, int finalSample) = 0;
            virtual void format(int sampleRate, int sampleSize, int channels) = 0;
            virtual float *loadSamples() = 0;
            virtual void unloadSamples(float *samples) = 0;
            virtual bool exportWave(const std::string &fileName) = 0;
            virtual bool exportAsCode(const std::string &fileName) = 0;
    };

} // RL

#endif //raylib_IWAVE_HPP
