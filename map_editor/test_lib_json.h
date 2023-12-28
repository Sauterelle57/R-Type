#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#ifndef RTYPE_TEST_LIB_JSON_H

    struct Entite {
        std::string type;
        int x;
        int y;
    };

    struct Conditions {
        int score_minimum;
        int nombre_ennemis_detruits;
    };

    struct Palier {
        int position_x;
        Conditions conditions;
        std::vector<Entite> entites;
    };

    struct stage_value {
        int niveau;
        std::vector<Palier> paliers;
    };

#define RTYPE_TEST_LIB_JSON_H

#endif //RTYPE_TEST_LIB_JSON_H
