# R-Type Project

This repository contains the source code for an R-Type game implemented in C++ using the SFML library for networking.

## Overview

The project structure is organized as follows:

### Renderer Folder

Contains various modules for rendering graphics and handling different aspects of the game interface:

- `Sound`
- `Camera`
- `Cursor`
- `Font`
- Other utility files for rendering

### Tools Folder

Contains utility modules necessary for the game:

- `Clock`
- `ECS` (Entity Component System)
- `Error`
- `Utils`
- `Vec3` and `Vec4`

### Source Files

- `UdpClient.hpp` and `UdpClient.cpp`: Implementations for UDP client functionality utilizing SFML for networking.
- `Core.hpp` and `Core.cpp`: Main game core handling rendering, entities, systems, and interactions.
- `IListener.hpp` and `Listener.hpp`: Implementations for listening to events in the game.
- `Main.cpp`: Main entry point for the game, setting up and running the core loop.

## Setting Up and Running

To run the game:

1. Clone this repository.
2. Compile the project using CMake and the appropriate build commands.
3. Execute the generated executable to start the game.

## How to Use

The `Core` class initializes the game core and systems, manages entities, and controls the game loop. Entities, components, and systems are set up here.

`UdpClient` facilitates UDP communication between the client and server for real-time game updates.

`Listener` implements event handling and entity creation based on received events from the server.

## Running the Game

To start the game:

1. Compile the code using the provided CMake configurations.
2. Run the generated executable.
3. Enjoy playing the R-Type game!


Feel free to contribute to the project or report any issues encountered!

