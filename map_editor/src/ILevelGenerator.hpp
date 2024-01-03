//
// Created by axell on 03/01/2024.
//

#ifndef MAP_EDITOR_ILEVELGENERATOR_HPP
    #define MAP_EDITOR_ILEVELGENERATOR_HPP

    #include <string>

    class ILevelGenerator {
    public:
        virtual ~ILevelGenerator() = default;

        virtual void startLevel(int stage) = 0;
        virtual void createStep(int posX, int scoreMin, int destroyed) = 0;
        virtual void addEntity(const std::string& type, int x, int y) = 0;
        virtual void endLevel() = 0;
        virtual void generateJSON(const std::string& filename) = 0;
    };


#endif //MAP_EDITOR_ILEVELGENERATOR_HPP
