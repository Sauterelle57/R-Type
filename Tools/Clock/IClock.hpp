/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IClock
*/

#ifndef RTYPE_ICLOCK_HPP
#define RTYPE_ICLOCK_HPP

#include <string>

namespace tls {
    class IClock {
        public:
            virtual ~IClock() = default;

            virtual std::string getTimeFromBeginning() = 0;
            virtual void stop() = 0;
            virtual bool isTimeElapsed() = 0;
            virtual void setInterval(float interval) = 0;
            virtual float getInterval() const = 0;
    };
}

#endif //RTYPE_ICLOCK_HPP
