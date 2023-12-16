/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IServerController
*/

#ifndef RTYPE_ISERVERCONTROLLER_HPP
#define RTYPE_ISERVERCONTROLLER_HPP

namespace rt {

    class IServerController {
    public:
        virtual ~IServerController() = default;
        virtual void run() = 0;
    };

} // rt

#endif //RTYPE_ISERVERCONTROLLER_HPP
