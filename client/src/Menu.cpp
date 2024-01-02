/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Menu
*/

#include <algorithm>
#include "Menu.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Image.hpp"
#include "renderer/Utils.hpp"
#include "renderer/Model.hpp"

namespace RT {
    Menu::Menu() {
        std::shared_ptr<RL::IImage> imgBackground = std::make_shared<RL::ZImage>("./client/resources/menu/background.png");
        imgBackground->resize(1920, 1080);

        _background = std::make_shared<RL::ZTexture>(*imgBackground->getImage());
        for (char c = 0; c <= '9'; c++) {
            std::string path = "./client/resources/menu/numbers/.png";
            RL::ZImage img(path.insert(32, 1, c));
            img.resize(200/3.5, 200/3.5);
            _numberMap[c] = std::make_shared<RL::ZTexture>(*img.getImage());
        }
        RL::ZImage img("./client/resources/menu/numbers/point.png");
        img.resize(200/3.5, 200/3.5);
        _numberMap['.'] = std::make_shared<RL::ZTexture>(*img.getImage());

        std::shared_ptr<RL::IImage> imgEnterGame = std::make_shared<RL::ZImage>("./client/resources/menu/EnterGame.png");
        imgEnterGame->resize(1000/3, 200/3);
        _enterGame = std::make_shared<RL::ZTexture>(*imgEnterGame->getImage());

        std::shared_ptr<RL::IImage> imgCursor = std::make_shared<RL::ZImage>("./client/resources/menu/arrow.png");
        imgCursor->resize(200/3, 200/3);
        _cursor = std::make_shared<RL::ZTexture>(*imgCursor->getImage());
    }

    unsigned int Menu::getPort() const {
        return _port;
    }

    void Menu::setPort(unsigned int port) {
        _port = port;
    }

    const std::string &Menu::getHost() const {
        return _host;
    }

    void Menu::setHost(const std::string &host) {
        _host = host;
    }

    static void displayText(std::map<char, std::shared_ptr<RL::ITexture>> _numberMap, std::string text, int x, int y, Color color) {
        int i = 0;
        for (auto &c : text) {
            _numberMap[c]->draw(x + (120/3.5)*i++, y, color);
        }
    }

    void Menu::loop(std::shared_ptr<RL::IWindow> &window, std::shared_ptr<RL::IEvent> &events, bool error) {
        bool status = true;
        std::string errorText = "Invalid target connexion";
        Color errorColor = {255, 0, 0, static_cast<unsigned char>((error ? 255 : 0))};

        while (status) {
            window->beginDrawing();
            window->clearBackground(RAYWHITE);

            if (errorColor.a > 0) errorColor.a -= 1;

            int size = 35;
            std::string port = std::to_string(_port);
            int lenHost = RL::Utils::measureText(_host, size);
            int lenPort = RL::Utils::measureText(port, size);

            if (events->isKeyPressed(KEY_DOWN)) {
                _focus = _focus == PORT ? ENTER : _focus;
                _focus = _focus == HOST ? PORT : _focus;
            }
            if (events->isKeyPressed(KEY_UP)) {
                _focus = _focus == PORT ? HOST : _focus;
                _focus = _focus == ENTER ? PORT : _focus;
            }
            if (events->isKeyPressed(KEY_TAB)) {
                if (_focus == PORT)
                    _focus = ENTER;
                else if (_focus == HOST)
                    _focus = PORT;
                else if (_focus == ENTER)
                    _focus = HOST;
            }

            if (events->isKeyPressed(KEY_ENTER)) {
                if (_focus == ENTER)
                    status = false;
                if (_focus == PORT)
                    _focus = ENTER;
                if (_focus == HOST)
                    _focus = PORT;
            }

            if (events->isKeyPressed(KEY_BACKSPACE)) {
                if (_focus == HOST && _host.size() > 0) {
                    _host.pop_back();
                }
                if (_focus == PORT && port.size() > 0) {
                    std::string tmp = std::to_string(_port);
                    tmp.pop_back();
                    if (tmp.size() > 0) {
                        try {
                            _port = std::clamp(std::stoi(tmp), 0, 65535);
                        } catch (std::exception &e) {
                            _port = 65535;
                        }
                    } else
                        _port = 0;
                }
            }

            int key = events->getKeyPressed();
            if ((key >= 48 && key <= 57) || events->isKeyPressed(KEY_COMMA)) {
                if (_focus == HOST && _host.size() < 20)
                    _host += (key == KEY_COMMA) ? KEY_PERIOD : key;
                if (_focus == PORT && key != KEY_COMMA && std::to_string(_port).size() < 5) {
                    std::string tmp = std::to_string(_port);
                    tmp += key;
                    try {
                        _port = std::clamp(std::stoi(tmp), 0, 65535);
                    } catch (std::exception &e) {
                        _port = 65535;
                    }
                }
            }

            if (window->shouldClose()) exit(0);

            port = std::to_string(_port);
            int lenError = RL::Utils::measureText(errorText, 20);
            _background->draw(0, 0, WHITE);
            _cursor->draw(200, _focus == HOST ? 695 : _focus == PORT ? 745 : 800, WHITE);
            displayText(_numberMap, _host, 250, 700, _focus == HOST ? WHITE : GRAY);
            displayText(_numberMap, port, 250, 750, _focus == PORT ? WHITE : GRAY);
            _enterGame->draw(250, 800, _focus == ENTER ? WHITE : GRAY);


            window->endDrawing();
        }
    }

} // RT
