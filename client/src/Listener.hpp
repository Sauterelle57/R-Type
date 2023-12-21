/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Listener.hpp
*/

#ifndef RTYPE_LISTENER_HPP
#define RTYPE_LISTENER_HPP

#include "IListener.hpp"

namespace RT {
    class Listener : public IListener {
        public:
            ~Listener() = default;
            void onEvent() {

            }
    };
}

#endif //RTYPE_LISTENER_HPP
