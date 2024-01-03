//
// Created by axell on 03/01/2024.
//

#include "LevelGenerator.hpp"

namespace map {

    LevelGenerator::LevelGenerator() = default;

    void LevelGenerator::startLevel(int stage) {
        nlohmann::json level;
        level["stage"] = stage;
        level["step"] = nlohmann::json::array();
        levels.push_back(level);
        currentLevel = &levels.back();
    }

    void LevelGenerator::createStep(int posX, int scoreMin, int destroyed) {
        nlohmann::json step;
        step["pos_x"] = posX;
        step["conditions"]["score_min"] = scoreMin;
        step["conditions"]["destroyed"] = destroyed;
        currentLevel->at("step").push_back(step);
    }


    void LevelGenerator::addEntity(const std::string& type, int x, int y) {
        nlohmann::json entity;
        entity["type"] = type;
        entity["x"] = x;
        entity["y"] = y;

        if (!currentLevel->at("step").empty()) {
            currentLevel->at("step").back()["entity"].push_back(entity);
        } else {
            std::cerr << "Erreur : Aucune étape créée pour ajouter l'entité." << std::endl;
        }
    }

    void LevelGenerator::endLevel() {
        // Optionally, you can perform any cleanup or finalization for the level here.
    }

    void LevelGenerator::generateJSON(const std::string& filename) {
        std::ofstream file(filename);
        file << std::setw(4) << levels << std::endl;
        std::cout << "Fichier JSON généré avec succès : " << filename << std::endl;
    }

} // map