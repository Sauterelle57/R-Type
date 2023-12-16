/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** ServerController.hpp
*/

#ifndef SERVERCONTROLLER_HPP_
#define SERVERCONTROLLER_HPP_

#include "AsioWrapper.hpp"
#include <iostream>

namespace rt {

    class ServerController {
        public:
            ServerController(short port);

            void run();

            void handleReceivedData(const boost::system::error_code& error, std::size_t bytes_transferred);

        private:
            AsioWrapper asioWrapper;
    };

}

#endif /* !SERVERCONTROLLER_HPP_ */
