/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** GameController
*/

#ifndef GAMECONTROLLER_HPP_
#define GAMECONTROLLER_HPP_
#include "IGameController.hpp"

namespace rt {

    class GameController : public IGameController {
        public:
            GameController() = default;
            ~GameController() = default;
            int exec() { return this->i++; }
        private:
            int i = 0;
    };

}

#endif /* !GAMECONTROLLER_HPP_ */
