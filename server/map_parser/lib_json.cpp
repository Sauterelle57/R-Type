#include "lib_json.hpp"
#include "Parser.hpp"

lvl::StageValue json_parsing(const std::string& path) {
    lvl::JsonParser json_parser(path);

    lvl::StageValue result;
    result.stage = json_parser.get<int>("stage");

    auto steps = json_parser.get<nlohmann::json>("step");
    for (const auto& step : steps) {
        lvl::Step p;
        p.pos_x = step["pos_x"].get<int>();

        if (step.find("conditions") != step.end()) {
            auto conditions = step["conditions"];
            p.conditions.score_min = conditions.value("score_min", 0);
            p.conditions.destroyed = conditions.value("destroyed", 0);
        }

        auto entities = step["entity"].get<std::vector<nlohmann::json>>();
        for (const auto& entity : entities) {
            lvl::Entity e;
            e.type = entity["type"].get<std::string>();
            e.x = entity["x"].get<int>();
            e.y = entity["y"].get<int>();
            p.entity.push_back(e);
        }

        result.step.push_back(p);
    }

    return result;
}

int main() {
    const std::string path = "map_editor/map_test.json";
    lvl::StageValue data = json_parsing(path);

    std::cout << "Niveau : " << data.stage << std::endl;

    for (const auto& step : data.step) {
        std::cout << "Position X du palier : " << step.pos_x << std::endl;

        std::cout << "Conditions du palier :" << std::endl;
        std::cout << "Score minimum : " << step.conditions.score_min << std::endl;
        std::cout << "Nombre d'ennemis detruits minimum : " << step.conditions.destroyed << std::endl;

        std::cout << "Entités du palier :" << std::endl;
        for (const auto& entity : step.entity) {
            std::cout << "  Type : " << entity.type << ", Position : (" << entity.x << ", " << entity.y << ")" << std::endl;
        }
    }

    return 0;
}
