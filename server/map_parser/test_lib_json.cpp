#include "test_lib_json.hpp"
#include "Parser.hpp"

using json = nlohmann::json;

lvl::StageValue json_parsing(const std::string& path) {
    std::ifstream jsonFile(path);
    if (!jsonFile.is_open()) {
        std::cerr << "Error loading JSON file." << std::endl;
        return lvl::StageValue{};
    }

    json data;
    jsonFile >> data;

    lvl::StageValue result;
    result.stage = data["stage"];

    for (const auto& step : data["step"]) {
        lvl::Step p;
        p.pos_x = step["pos_x"];

        if (step.find("conditions") != step.end()) {
            auto conditions = step["conditions"];
            p.conditions.score_min = conditions.value("score_min", 0);
            p.conditions.destroyed = conditions.value("destroyed", 0);
            // Add other conditions as needed
        }

        for (const auto& entity : step["entity"]) {
            lvl::Entity e;
            e.type = entity["type"];
            e.x = entity["x"];
            e.y = entity["y"];
            p.entity.push_back(e);
        }

        result.step.push_back(p);
    }

    return result;
}

int main() {

    lvl::Parser json("map_editor/map_test.json");



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
