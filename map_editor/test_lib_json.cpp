#include "test_lib_json.hpp"

using json = nlohmann::json;

stage_value json_parsing(const std::string& path) {
    std::ifstream fichier_json(path);
    if (!fichier_json.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier JSON." << std::endl;
        return stage_value{};
    }

    json donnees;
    fichier_json >> donnees;

    stage_value result;
    result.stage = donnees["stage"];

    for (const auto& palier : donnees["paliers"]) {
        Palier p;
        p.pos_x = palier["pos_x"];

        if (palier.find("conditions") != palier.end()) {
            auto conditions = palier["conditions"];
            p.conditions.score_min = conditions.value("score_min", 0);
            p.conditions.destroyed = conditions.value("destroyed", 0);
            // Add other conditions as needed
        }

        for (const auto& entite : palier["entites"]) {
            Entite e;
            e.type = entite["type"];
            e.x = entite["x"];
            e.y = entite["y"];
            p.entites.push_back(e);
        }

        result.paliers.push_back(p);
    }

    return result;
}

int main() {
    const std::string chemin_fichier = "map_editor/map_test.json";
    stage_value donnees = json_parsing(chemin_fichier);

    std::cout << "Niveau : " << donnees.stage << std::endl;

    for (const auto& palier : donnees.paliers) {
        std::cout << "Position X du palier : " << palier.pos_x << std::endl;

        std::cout << "Conditions du palier :" << std::endl;
        std::cout << "Score minimum : " << palier.conditions.score_min << std::endl;
        std::cout << "Nombre d'ennemis detruits minimum : " << palier.conditions.destroyed << std::endl;

        std::cout << "Entités du palier :" << std::endl;
        for (const auto& entite : palier.entites) {
            std::cout << "  Type : " << entite.type << ", Position : (" << entite.x << ", " << entite.y << ")" << std::endl;
        }
    }

    return 0;
}
