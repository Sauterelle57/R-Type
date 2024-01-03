//
// Created by axell on 03/01/2024.
//

#ifndef MAP_EDITOR_LEVELGENERATOR_HPP
#define MAP_EDITOR_LEVELGENERATOR_HPP

#include "ILevelGenerator.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <limits>

namespace map {

    class LevelGenerator : public ILevelGenerator {
    public:
        LevelGenerator();
        void startLevel(int stage) override;
        void createStep(int posX, int scoreMin, int destroyed) override;
        void addEntity(const std::string& type, int x, int y) override;
        void endLevel() override;
        void generateJSON(const std::string& filename) override;

    private:
        nlohmann::json levels;
        nlohmann::json* currentLevel{};
    };

} // map

#endif //MAP_EDITOR_LEVELGENERATOR_HPP
