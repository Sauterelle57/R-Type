/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LibJson.hpp
*/

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "Parser.hpp"

#ifndef RTYPE_TEST_LIB_JSON_H

namespace lvl {
    struct Entity {
        std::string type;
        float x;
        float y;
        float z;
        float shootSpeed;
    };

    struct Conditions {
        int score_min;
        int destroyed;
    };

    struct Step {
        int pos_x;
        std::string weapon;
        Conditions conditions;
        std::vector<Entity> entity;
    };

    struct StageValue {
        int stage;
        std::vector<Step> step;
    };

    StageValue jsonParsing(const std::string& path);
}


#define RTYPE_TEST_LIB_JSON_H

#endif //RTYPE_TEST_LIB_JSON_H