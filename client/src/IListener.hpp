/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ilistener.hpp
*/

#ifndef RTYPE_ILISTENER_HPP
#define RTYPE_ILISTENER_HPP

#include <string>

namespace RT {
    class IListener {
        public:
            virtual ~IListener() = default;

            virtual void onEvent() = 0;

            virtual void addEvent(const std::string &event) = 0;
    };
}

#endif //RTYPE_ILISTENER_HPP
