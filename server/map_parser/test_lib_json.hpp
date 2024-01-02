#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#ifndef RTYPE_TEST_LIB_JSON_H

    namespace lvl {
        struct Entity {
            std::string type;
            int x;
            int y;
        };

        struct Conditions {
            int score_min;
            int destroyed;
        };

        struct Step {
            int pos_x;
            Conditions conditions;
            std::vector<Entity> entity;
        };

        struct StageValue {
            int stage;
            std::vector<Step> step;
        };
    }
#define RTYPE_TEST_LIB_JSON_H

#endif //RTYPE_TEST_LIB_JSON_H
