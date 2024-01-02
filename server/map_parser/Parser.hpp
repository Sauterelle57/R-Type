//
// Created by axell on 02/01/2024.
//

#ifndef RTYPE_PARSER_HPP
#define RTYPE_PARSER_HPP

#include "IParser.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

namespace lvl {

    class Parser : public::IParser {
        private:
            std::unique_ptr<nlohmann::json> _data;

        public:
            Parser(const std::string& filename);
            int get_key(const std::string& key) const;
            int operator[](const std::string& key) const;
    };

} // lvl

#endif //RTYPE_PARSER_HPP
