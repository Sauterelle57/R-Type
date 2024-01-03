#ifndef RTYPE_JSONPARSER_HPP
#define RTYPE_JSONPARSER_HPP

#include <fstream>
#include <string>
#include <memory>
#include <vector>

namespace lvl {

    template<typename JsonLibrary>
    class JsonHandler {
        public:
            JsonHandler(const std::string& content) {
                _data = JsonLibrary::parse(content);
            }

            template <typename T>
            T get(const std::string& key) const {
                return _data.at(key).template get<T>();
            }

        private:
            JsonLibrary _data;
    };


    template<typename JsonLibrary>
    class JsonParser {
        public:
            JsonParser(const std::string& filename) {
                std::ifstream file(filename);
                if (!file.is_open()) {
                    throw std::runtime_error("Error opening: " + filename + " file");
                }
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                _handler = std::make_shared<JsonHandler<JsonLibrary>>(content);
            }

            template <typename T>
            T get(const std::string& key) const {
                try {
                    return _handler->template get<T>(key);
                } catch (...) {
                    throw std::runtime_error("JSON parsing error on " + key);
                }
            }

        private:
            std::shared_ptr<JsonHandler<JsonLibrary>> _handler;
    };

} // namespace lvl

#endif //RTYPE_JSONPARSER_HPP
