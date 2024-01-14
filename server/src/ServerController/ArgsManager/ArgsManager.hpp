/*
** EPITECH PROJECT, 2024
** ArgsManager
** File description:
** ArgsManager
*/

#ifndef ARGSMANAGER_HPP_
#define ARGSMANAGER_HPP_
#include "IArgsManager.hpp"
#include <cctype>

namespace rt {

    class ArgsManager : public IArgsManager {
        public:
            ArgsManager() = default;
            ~ArgsManager() = default;

            std::optional<int> getServerPort(int argc, char **argv) const {
                for (int i = 1; i < argc; i++) {
                    if (std::string(argv[i]) == "-p") {
                        if (i + 1 < argc) {
                            for (int x = 0; argv[i + 1][x]; x++) {
                                if (!std::isdigit(argv[i + 1][x]))
                                    return std::make_optional<int>(-1);
                            }
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

            bool hasDebugFlag(int argc, char **argv) const {
                for (int i = 1; i < argc; i++) {
                    if (std::string(argv[i]) == "-d" || std::string(argv[i]) == "--debug")
                        return true;
                }
                return false;
            }

            std::optional<std::string> getMapFilePath(int argc, char **argv) const {
                for (int i = 1; i < argc; i++) {
                    if (std::string(argv[i]) == "-m") {
                        if (i + 1 < argc) {
                            return std::string(argv[i + 1]);
                        } else {
                            return std::nullopt;
                        }
                    }
                }
                return std::nullopt;
            }
    };

}

#endif /* !ARGSMANAGER_HPP_ */
