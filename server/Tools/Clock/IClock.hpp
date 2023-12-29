//
// Created by noah on 12/19/23.
//

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
