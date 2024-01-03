#include "map_editor.hpp"
#include "LevelGenerator.hpp"

bool isValidInput(const std::string& input) {
    return input.find_first_not_of("0123456789") == std::string::npos;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getTotalLevels() {
    int totalLevels;
    do {
        std::cout << "\nEnter the total number of levels you want to create: ";
        std::cin >> totalLevels;

        if (std::cin.fail() || totalLevels <= 0) {
            std::cout << "Invalid input. Please enter a positive integer.\n";
            clearInputBuffer();
        } else {
            break;
        }

    } while (true);
    return totalLevels;
}

int getTotalSteps(int currentLevel) {
    int totalSteps;
    do {
        std::cout << "\nEnter the total number of steps for Level " << currentLevel << ": ";
        std::cin >> totalSteps;

        if (std::cin.fail() || totalSteps <= 0) {
            std::cout << "Invalid input. Please enter a positive integer.\n";
            clearInputBuffer();
        } else {
            break;
        }

    } while (true);
    return totalSteps;
}

int getIntegerInput(const std::string& prompt) {
    int input;
    do {
        std::cout << prompt;
        std::string inputStr;
        std::cin >> inputStr;

        if (isValidInput(inputStr)) {
            std::stringstream(inputStr) >> input;
            if (input > 0) {
                break;
            }
        }
        std::cout << "Invalid input. Please enter a positive integer.\n";
        clearInputBuffer();

    } while (true);
    return input;
}


void createStep(map::LevelGenerator& generator, int currentLevel, int currentStep) {
    std::cout << "\nCreating Step " << currentStep << " for Level " << currentLevel << ":\n";

    int startingPositionX = getIntegerInput("Enter starting X position for the step (integer): ");
    int minimumScore = getIntegerInput("Enter minimum score required to advance to the next step (integer): ");
    int destroyedEnemies = getIntegerInput("Enter number of destroyed enemies required to advance to the next step (integer): ");

    generator.startLevel(currentLevel);
    generator.createStep(startingPositionX, minimumScore, destroyedEnemies);

    std::cout << "\nStep created successfully!\n";
}

void addEntityToStep(map::LevelGenerator& generator) {
    char addEntityChoice;
    do {
        std::cout << "\nDo you want to add an entity to this step? (Y/N): ";
        std::cin >> addEntityChoice;

        if (addEntityChoice == 'Y' || addEntityChoice == 'y') {
            std::string entityType;
            int entityX = getIntegerInput("Enter entity X position (integer): ");
            int entityY = getIntegerInput("Enter entity Y position (integer): ");

            std::cout << "Enter entity type: ";
            std::cin >> entityType;

            generator.addEntity(entityType, entityX, entityY);
            std::cout << "Entity added successfully!\n";
        }
    } while (addEntityChoice == 'Y' || addEntityChoice == 'y');
}

void generateLevels(map::LevelGenerator& generator, int totalLevels) {
    for (int currentLevel = 1; currentLevel <= totalLevels; currentLevel++) {
        std::cout << "\nCreating Level " << currentLevel << ":\n";
        int totalSteps = getTotalSteps(currentLevel);

        for (int currentStep = 1; currentStep <= totalSteps; ++currentStep) {
            createStep(generator, currentLevel, currentStep);
            addEntityToStep(generator);
        }

        generator.endLevel();
        std::cout << "\nLevel " << currentLevel << " completed!\n";

        if (currentLevel < totalLevels) {
            std::cout << "\nPress Enter to proceed to the next level...\n";
            clearInputBuffer();
            std::cin.get();
        }
    }
}

int main() {
    map::LevelGenerator generator;

    std::cout << "Welcome to the Level Generator!\n";

    int totalLevels = getTotalLevels();
    generateLevels(generator, totalLevels);

    std::string filename;
    clearInputBuffer();
    std::cout << "\nEnter the desired filename for the final JSON file (default: levels.json): ";
    std::getline(std::cin, filename);

    if (filename.empty()) {
        filename = "levels.json";
    } else if (filename.find(".json") == std::string::npos) {
        filename += ".json";
    }
    generator.generateJSON(filename);
    std::cout << "\nJSON file generated successfully: " << filename << "\n";
    std::cout << "\nPress Enter to exit...";
    clearInputBuffer();
    std::cin.get();

    return 0;
}
