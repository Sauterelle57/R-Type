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
        int score_min;
        int destroyed;
    };

    struct Palier {
        int pos_x;
        Conditions conditions;
        std::vector<Entite> entites;
    };

    struct stage_value {
        int stage;
        std::vector<Palier> paliers;
    };

#define RTYPE_TEST_LIB_JSON_H

#endif //RTYPE_TEST_LIB_JSON_H
