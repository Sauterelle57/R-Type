/*
** EPITECH PROJECT, 2023
** ClientController.hpp
** File description:
** ClientController
*/

#ifndef CLIENTCONTROLLER_HPP_
#define CLIENTCONTROLLER_HPP_
#include "Client.hpp"
#include <memory>
#include <map>

namespace rt 
{
    class ClientController {
        public:
            ClientController() = default;
            ~ClientController() = default;
            
            void addClient(const std::string &ip, const int port) {
                std::cout << "CLIENTMGR/NEW CLIENT: " << ip << ":" << port << std::endl;
                _clients[ip + ":" + std::to_string(port)] = std::make_shared<Client>(ip, port);
            };
            void removeClient(const std::string &ip, const int port) {
                _clients.erase(ip + ":" + std::to_string(port));
            };
            bool isClientExist(const std::string &ip, const int port) {
                return _clients.find(ip + ":" + std::to_string(port)) != _clients.end();
            };
            void addPlayerID(const std::string &ip, const int port, const int id) {
                std::cout << "SERVER/CLIENTMGR: " << ip << ":" << port << " has been assigned ID: " << id << std::endl;
                _clients[ip + ":" + std::to_string(port)]->setPlayerID(id);
            };
            int getPlayerID(const std::string &ip, const int port) {
                return _clients[ip + ":" + std::to_string(port)]->getPlayerID();
            };
            int checkClientIDExist(const int id) {
                for (auto const &client : _clients) {
                    if (client.second->getPlayerID() == id) {
                        return 1;
                    }
                }
                return 0;
            };
        private:
            std::map<std::string, std::shared_ptr<Client>> _clients;
    };

}

#endif /* !CLIENTCONTROLLER_HPP_ */
