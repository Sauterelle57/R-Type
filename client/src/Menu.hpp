/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <map>
#include <memory>
#include "renderer/IWindow.hpp"
#include "renderer/IEvent.hpp"
#include "renderer/IImage.hpp"
#include "renderer/IModel.hpp"
#include "renderer/ITexture.hpp"

namespace RT {
    enum Focus {
        HOST,
        PORT,
        ENTER
    };

    class Menu {
        public:
            Menu();
            ~Menu() = default;

            void loop(std::shared_ptr<RL::IWindow> &window, std::shared_ptr<RL::IEvent> &event, bool error);

            unsigned int getPort() const;
            void setPort(unsigned int port);

            const std::string &getHost() const;
            void setHost(const std::string &host);

            unsigned int _port = 4242;
            std::string _host = "127.0.0.1";
            Focus _focus = HOST;

            std::shared_ptr<RL::ITexture> _background;
            std::map<char, std::shared_ptr<RL::ITexture>> _numberMap;
            std::shared_ptr<RL::ITexture> _enterGame;
            std::shared_ptr<RL::ITexture> _cursor;


    };
} // RT

#endif /* !MENU_HPP_ */
