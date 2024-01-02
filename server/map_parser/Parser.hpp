#ifndef RTYPE_JSONPARSER_HPP
#define RTYPE_JSONPARSER_HPP

#include <fstream>
#include <string>
#include <memory>
#include <exception>

namespace lvl {

    class JsonParser {
        public:
            JsonParser(const std::string& filename) {
                std::ifstream file(filename);
                if (!file.is_open()) {
                    throw std::runtime_error("Error opening: " + filename + " file");
                }
                file >> _data;
            }

            template <typename T>
            T get_key(const std::string& key) const {
                try {
                    return _data.at(key).get<T>();
                } catch (...) {
                    throw std::runtime_error("JSON parsing error on " + key);
                }
            }

            template <typename T>
            std::vector<T> get_list(const std::string& key) const {
                try {
                    std::vector<T> list;
                    for (const auto& item : _data.at(key)) {
                        list.push_back(item.get<T>());
                    }
                    return list;
                } catch (...) {
                    throw std::runtime_error("JSON parsing error on " + key);
                }
            }

        private:
            nlohmann::json _data;
    };

} // namespace lvl

#endif //RTYPE_JSONPARSER_HPP
