### Level Generator User Interface Guide

#### Prerequisites

Before starting, ensure you have the following:

1. CMake installed on your system.

#### Compilation

1. Clone the Level Generator repository:

    ```bash
    git clone https://github.com/your_username/level-generator.git
    ```

   Replace `your_username` with your actual GitHub username.

2. Navigate to the project directory:

    ```bash
    cd level-generator
    ```

3. Create a build directory:

    ```bash
    mkdir build
    cd build
    ```

4. Run CMake to generate the build files:

    ```bash
    cmake ..
    ```

5. Build the executable:

    ```bash
    make
    ```

#### Running the Program

1. After successfully compiling the program, run it:

    ```bash
    ./LevelGenerator
    ```

#### Creating Levels

Follow the on-screen instructions to create levels and steps. The program will prompt you to enter various details for each level and step, such as starting X position, minimum score, destroyed enemies, and entities.

- When prompted for the filename for the final JSON file, you can either provide a custom filename or press Enter to use the default filename "levels.json".

#### Completing the Process

After finishing all the levels and steps, the program will generate the final JSON file. It will display a success message along with the filename.

#### Exiting the Program

To exit the program, press Enter when prompted to do so.

### Additional Notes

- Ensure your terminal supports the features required by the program.

- If you encounter any issues during compilation or execution, check for error messages and make sure you have fulfilled the prerequisites.

This guide provides a basic overview of using the Level Generator program. If you have specific questions or encounter difficulties, feel free to reach out for assistance.