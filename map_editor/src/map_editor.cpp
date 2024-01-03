#include "map_editor.hpp"
#include "LevelGenerator.hpp"

// Function to validate user input
bool isValidInput(const std::string& input) {
    return input.find_first_not_of("0123456789") == std::string::npos;
}

// Function to clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


int main() {
    map::LevelGenerator generator;

    std::cout << "Welcome to the Level Generator!\n";

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

    for (int currentLevel = 1; currentLevel <= totalLevels; currentLevel++) {
        std::cout << "\nCreating Level " << currentLevel << ":\n";

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

        for (int currentStep = 1; currentStep <= totalSteps; ++currentStep) {
            std::cout << "\nCreating Step " << currentStep << " for Level " << currentLevel << ":\n";

            // Asking for level details
            int startingPositionX, minimumScore, destroyedEnemies;

            do {
                std::cout << "Enter starting X position for the step (integer): ";
                std::cin >> startingPositionX;

                if (std::cin.fail() || startingPositionX <= 0) {
                    std::cout << "Invalid input. Please enter a positive integer.\n";
                    clearInputBuffer();
                } else {
                    break;
                }

            } while (true);

            do {
                std::cout << "Enter minimum score required to advance to the next step (integer): ";
                std::cin >> minimumScore;

                if (std::cin.fail() || minimumScore <= 0) {
                    std::cout << "Invalid input. Please enter a positive integer.\n";
                    clearInputBuffer();
                } else {
                    break;
                }

            } while (true);

            do {
                std::cout << "Enter number of destroyed enemies required to advance to the next step (integer): ";
                std::cin >> destroyedEnemies;

                if (std::cin.fail() || destroyedEnemies <= 0) {
                    std::cout << "Invalid input. Please enter a positive integer.\n";
                    clearInputBuffer();
                } else {
                    break;
                }

            } while (true);

            // Creating the step
            generator.startLevel(currentLevel);
            generator.createStep(startingPositionX, minimumScore, destroyedEnemies);

            std::cout << "\nStep created successfully!\n";

            // Adding entities to the step
            char addEntityChoice;
            do {
                std::cout << "\nDo you want to add an entity to this step? (Y/N): ";
                std::cin >> addEntityChoice;

                if (addEntityChoice == 'Y' || addEntityChoice == 'y') {
                    std::string entityType;
                    int entityX, entityY;

                    std::cout << "Enter entity type: ";
                    std::cin >> entityType;

                    do {
                        std::cout << "Enter entity X position (integer): ";
                        std::string input;
                        std::cin >> input;

                        if (isValidInput(input)) {
                            std::stringstream(input) >> entityX;
                            break;
                        } else {
                            std::cout << "Invalid input. Please enter an integer.\n";
                        }

                    } while (true);

                    do {
                        std::cout << "Enter entity Y position (integer): ";
                        std::string input;
                        std::cin >> input;

                        if (isValidInput(input)) {
                            std::stringstream(input) >> entityY;
                            break;
                        } else {
                            std::cout << "Invalid input. Please enter an integer.\n";
                        }

                    } while (true);

                    generator.addEntity(entityType, entityX, entityY);
                    std::cout << "Entity added successfully!\n";
                }
            } while (addEntityChoice == 'Y' || addEntityChoice == 'y');
        }

        generator.endLevel();

        std::cout << "\nLevel " << currentLevel << " completed!\n";

        if (currentLevel < totalLevels) {
            std::cout << "\nPress Enter to proceed to the next level...\n";
            clearInputBuffer();
            std::cin.get();
        }

    }

    std::string filename;
    clearInputBuffer(); // Clear any input errors
    std::cout << "\nEnter the desired filename for the final JSON file (default: levels.json): ";
    std::getline(std::cin, filename);

    // If the user doesn't provide a filename, use the default
    if (filename.empty()) {
        filename = "levels.json";
    } else if (filename.find(".json") == std::string::npos) {
        // If the user provides a filename without the .json extension, add it
        filename += ".json";
    }

    // Generate the final JSON file
    generator.generateJSON(filename);

    std::cout << "\nJSON file generated successfully: " << filename << "\n";

    // Prompt to keep the console open
    std::cout << "\nPress Enter to exit...";
    clearInputBuffer();
    std::cin.get();

    return 0;
}
