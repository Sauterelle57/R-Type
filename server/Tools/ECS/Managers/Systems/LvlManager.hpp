/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LvlManager.hpp
*/

#ifndef RTYPE_LVLMANAGER_HPP
#define RTYPE_LVLMANAGER_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "../Components/ComponentStructs.hpp"

namespace rt {
    class GameController;
}

namespace ECS {
    class LvlManager : public System {
        public:
            void update(rt::GameController &gameController);
    };
}

#endif //RTYPE_LVLMANAGER_HPP
