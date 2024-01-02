#ifndef RTYPE_JSONPARSER_HPP
#define RTYPE_JSONPARSER_HPP

#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "nlohmann/json.hpp"

namespace lvl {

    class JsonHandler {
        public:
            JsonHandler(const std::string& content) {
                _data = nlohmann::json::parse(content);
            }

            template <typename T>
            T get(const std::string& key) const {
                return _data.at(key).get<T>();
            }

        private:
            nlohmann::json _data;
    };

    class JsonParser {
        public:
            JsonParser(const std::string& filename) {
                std::ifstream file(filename);
                if (!file.is_open()) {
                    throw std::runtime_error("Error opening: " + filename + " file");
                }
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                _handler = std::make_shared<JsonHandler>(content);
            }

            template <typename T>
            T get(const std::string& key) const {
                try {
                    return _handler->get<T>(key);
                } catch (...) {
                    throw std::runtime_error("JSON parsing error on " + key);
                }
            }

        private:
            std::shared_ptr<JsonHandler> _handler;
    };

} // namespace lvl

#endif //RTYPE_JSONPARSER_HPP
