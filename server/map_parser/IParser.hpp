//
// Created by axell on 02/01/2024.
//

#ifndef RTYPE_IPARSER_HPP
#define RTYPE_IPARSER_HPP


#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

namespace lvl {

    template <typename T>
    class JsonValue {
    public:
        JsonValue() : _data(nullptr) {}

        JsonValue(const nlohmann::json* data) : _data(data) {}

        T get() const {
            if (_data && _data->is<T>()) {
                return _data->get<T>();
            } else {
                std::cerr << "Invalid conversion." << std::endl;
                return T();
            }
        }

    private:
        const nlohmann::json* _data;
    };

    class Parser {
    public:
        Parser(const std::string& filename);
        template <typename T>
        JsonValue<T> get_key(const std::string& key) const;

    private:
        nlohmann::json _data;
    };

    Parser::Parser(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> _data;
            file.close();
        } else {
            throw std::runtime_error("Erreur lors de l'ouverture du fichier JSON.");
        }
    }

    template <typename T>
    JsonValue<T> Parser::get_key(const std::string& key) const {
        auto it = _data.find(key);
        if (it != _data.end()) {
            if constexpr (std::is_same<T, int>::value ||
                          std::is_same<T, double>::value ||
                          std::is_same<T, std::string>::value ||
                          std::is_same<T, bool>::value) {
                return JsonValue<T>(&it.value());
            } else {
                static_assert(std::is_same<T, int>::value || std::is_same<T, double>::value ||
                              std::is_same<T, std::string>::value || std::is_same<T, bool>::value,
                              "Unsupported type");
            }
        } else {
            std::cerr << key << " key not found in JSON." << std::endl;
            return JsonValue<T>();
        }
    }

} // namespace lvl




#endif //RTYPE_IPARSER_HPP
