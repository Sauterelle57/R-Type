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
            std::vector<std::shared_ptr<Client>> getClients() const {
                std::vector<std::shared_ptr<Client>> clients;
                for (const auto &client : _clients) {
                    clients.push_back(client.second);
                }
                return clients;
            };
            std::shared_ptr<Client> getClient(const std::string &ip, const int port) {
                return _clients[ip + ":" + std::to_string(port)];
            }

        private:
            std::map<std::string, std::shared_ptr<Client>> _clients;
    };

}

#endif /* !CLIENTCONTROLLER_HPP_ */
