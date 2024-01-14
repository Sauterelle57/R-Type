/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IArgsManager
*/

#ifndef IARGSMANAGER_HPP_
#define IARGSMANAGER_HPP_
#include <iostream>
#include <cstdlib>
#include <optional>

namespace rt {

    class IArgsManager {
        public:
            virtual ~IArgsManager() = default;
            virtual std::optional<int> getServerPort(int argc, char* argv[]) const = 0;
            virtual bool hasHelpFlag(int argc, char **argv) const = 0;
    };

}

#endif /* !IARGSMANAGER_HPP_ */
