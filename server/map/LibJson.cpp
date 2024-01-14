/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LibJson.cpp
*/

#include "LibJson.hpp"
#include "Parser.hpp"
#include "nlohmann/json.hpp"

namespace lvl {
    StageValue jsonParsing(const std::string& path) {
        JsonParser<nlohmann::json> json_parser(path);

        StageValue result;
        result.stage = json_parser.get<int>("stage");

        auto steps = json_parser.get<nlohmann::json>("step");
        for (const auto& step : steps) {
            Step p;
            p.pos_x = step["pos_x"].get<int>();

            if (step.find("conditions") != step.end()) {
                auto conditions = step["conditions"];
                p.conditions.score_min = conditions.value("score_min", 0);
                p.conditions.destroyed = conditions.value("destroyed", 0);
            }

            auto entities = step["entity"].get<std::vector<nlohmann::json>>();
            for (const auto& entity : entities) {
                Entity e;
                e.type = entity["type"].get<std::string>();
                e.x = entity["x"].get<double>();
                e.y = entity["y"].get<double>();
                e.z = entity["z"].get<double>();
                e.shootSpeed = entity["shootSpeed"].get<double>();
                p.entity.push_back(e);
            }

            result.step.push_back(p);
        }

        return result;
    }
}
