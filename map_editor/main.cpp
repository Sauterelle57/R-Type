#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Evenement {
public:
    std::string type;
    int position_x;
    int position_y;
    std::vector<json> ennemis;
    std::vector<json> bonus;
};

class Niveau {
public:
    int niveau;
    std::vector<Evenement> evenements;
};

int main() {
    std::ifstream fichier_json("chemin/vers/le/fichier.json");
    if (!fichier_json.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier JSON" << std::endl;
        return 1;
    }

    json donnees;
    fichier_json >> donnees;

    Niveau niveau;
    niveau.niveau = donnees["niveau"];

    for (const auto& evenement_data : donnees["evenements"]) {
        Evenement evenement;
        evenement.type = evenement_data["type"];
        evenement.position_x = evenement_data["position_x"];
        evenement.position_y = evenement_data["position_y"];

        for (const auto& ennemi_data : evenement_data["ennemis"]) {
            evenement.ennemis.push_back(ennemi_data);
        }

        for (const auto& bonus_data : evenement_data["bonus"]) {
            evenement.bonus.push_back(bonus_data);
        }

        niveau.evenements.push_back(evenement);
    }

    // Vous pouvez maintenant utiliser les données du niveau comme nécessaire
    std::cout << "Niveau " << niveau.niveau << std::endl;

    for (const auto& evenement : niveau.evenements) {
        std::cout << "Evenement de type " << evenement.type << " à la position (" 
                  << evenement.position_x << ", " << evenement.position_y << ")" << std::endl;

        std::cout << "Ennemis :" << std::endl;
        for (const auto& ennemi : evenement.ennemis) {
            std::cout << "Type : " << ennemi["type"] << ", x : " << ennemi["x"] << ", y : " << ennemi["y"] << std::endl;
        }

        std::cout << "Bonus :" << std::endl;
        for (const auto& bonus : evenement.bonus) {
            std::cout << "Type : " << bonus["type"] << ", x : " << bonus["x"] << ", y : " << bonus["y"] << std::endl;
        }
    }

    return 0;
}
