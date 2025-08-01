/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Wave.hpp
*/

#ifndef raylib_WAVE_HPP
#define raylib_WAVE_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IWave.hpp"

namespace RL {

    class ZWave : public IWave {
        public:
            ZWave(const std::string &fileName) {
                _wave = std::make_unique<Wave>(LoadWave(fileName.c_str()));
            };

            ~ZWave() {
                UnloadWave(*_wave);
            };

            bool isReady() {
                return IsWaveReady(*_wave);
            };
            Wave copy() {
                return WaveCopy(*_wave);
            };

            void crop(int initSample, int finalSample) {
                return WaveCrop(_wave.get(), initSample, finalSample);
            };

            void format(int sampleRate, int sampleSize, int channels) {
                return WaveFormat(_wave.get(), sampleRate, sampleSize, channels);
            };

            float *loadSamples() {
                return LoadWaveSamples(*_wave);
            };

            void unloadSamples(float *samples) {
                return UnloadWaveSamples(samples);
            };

            bool exportWave(const std::string &fileName) {
                return ExportWave(*_wave, fileName.c_str());
            };

            bool exportAsCode(const std::string &fileName) {
                return ExportWaveAsCode(*_wave, fileName.c_str());
            };

            std::unique_ptr<Wave> _wave;
    };

} // RL

#endif //raylib_WAVE_HPP
