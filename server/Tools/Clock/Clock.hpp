/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Clock.hpp
*/

#ifndef RTYPE_CLOCK_HPP
#define RTYPE_CLOCK_HPP

#include <chrono>
#include <string>
#include "IClock.hpp"

namespace tls {
    class Clock : public IClock {
        public:
            Clock(float interval) {
                _interval = interval;
                _start = std::chrono::system_clock::now();
                _end = std::chrono::system_clock::now();
            }
            Clock() {
                _start = std::chrono::system_clock::now();
                _end = std::chrono::system_clock::now();
            }
            ~Clock() = default;

            float getInterval() const {
                return _interval;
            }

            void setInterval(float interval) {
                _interval = interval;
            }

            bool isTimeElapsed() {
                _end = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsed_seconds = _end - _start;
                if (elapsed_seconds.count() >= _interval) {
                    _start = std::chrono::system_clock::now();
                    return true;
                }
                return false;
            }

            void stop() {
                if (!_stop)
                    _end = std::chrono::system_clock::now();
                _stop = true;
            }

            std::string getTimeFromBeginning() {
                if (!_stop)
                    _end = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsed_seconds = _end - _start;
                int minutes = elapsed_seconds.count() / 60;
                int seconds = static_cast<int>(elapsed_seconds.count()) % 60;
                return (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
            }

            static long long getTimeStamp() {
                auto currentTime = std::chrono::system_clock::now();
                auto currentTimeMs = std::chrono::time_point_cast<std::chrono::nanoseconds>(currentTime);
                auto epochMs = currentTimeMs.time_since_epoch();
                return std::chrono::duration_cast<std::chrono::nanoseconds>(epochMs).count();
            }

        private:
            std::chrono::time_point<std::chrono::system_clock> _start;
            std::chrono::time_point<std::chrono::system_clock> _end;
            float _interval;
            bool _stop = false;
    };

} // tls

#endif //RTYPE_CLOCK_HPP
