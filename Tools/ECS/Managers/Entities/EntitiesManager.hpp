/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntitiesManager
*/

#ifndef ENTITIESMANAGER_HPP_
#define ENTITIESMANAGER_HPP_

#include <cstdint>

using Entity = std::uint32_t;

const Entity MAX_ENTITIES = 5000;

class EntitiesManager {
    public:
        EntitiesManager();
        ~EntitiesManager();

    protected:
    private:
};

#endif /* !ENTITIESMANAGER_HPP_ */
