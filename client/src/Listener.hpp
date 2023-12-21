/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Listener.hpp
*/

#ifndef RTYPE_LISTENER_HPP
#define RTYPE_LISTENER_HPP

#include <queue>
#include <iostream>
#include <sstream>
#include "IListener.hpp"

namespace RT {
    class Listener : public IListener {
        public:
            ~Listener() = default;
            void onEvent() {
                while (!_queue.empty()) {
                    std::string front = _queue.front();
                    std::cout << "New event : " << front << std::endl;
                    _queue.pop();

                    std::stringstream ss(front);
                    for (std::string line; std::getline(ss, line, ' ');) {
                        std::cout << line << std::endl;
                    }
                    std::cout << "end" << std::endl;
                }
            }

            void addEvent(const std::string &event) {
                _queue.push(event);
            }

            std::queue<std::string> _queue;
    };
}

#endif //RTYPE_LISTENER_HPP
