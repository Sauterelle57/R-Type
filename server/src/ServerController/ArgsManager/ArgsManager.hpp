/*
** EPITECH PROJECT, 2024
** ArgsManager
** File description:
** ArgsManager
*/

#ifndef ARGSMANAGER_HPP_
#define ARGSMANAGER_HPP_
#include "IArgsManager.hpp"

namespace rt {

    class ArgsManager : public IArgsManager {
        public:
            ArgsManager() = default;
            ~ArgsManager() = default;

            std::optional<int> getServerPort(int argc, char **argv) const {
                for (int i = 1; i < argc; i++) {
                    if (std::string(argv[i]) == "-p") {
                        if (i + 1 < argc) {
                            int port = std::atoi(argv[i + 1]);
                            return port;
                        } else {
                            return std::nullopt;
                        }
                    }
                }
                return std::nullopt;
            }

            bool hasHelpFlag(int argc, char **argv) const {
                for (int i = 1; i < argc; i++) {
                    if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
                        return true;
                }
                return false;
            }
    };

}

#endif /* !ARGSMANAGER_HPP_ */
