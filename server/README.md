# RType Game Server

## Overview

The RType Game Server is a multiplayer server implementation for the classic scrolling shooter game RType. The server uses the Entity-Component-System (ECS) architecture for managing game entities and their behaviors. It communicates with clients using UDP and utilizes the Boost.Asio library for asynchronous I/O operations.

## Table of Contents

- [Dependencies](#dependencies)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Contributing](#contributing)
- [License](#license)

## Dependencies

The project has the following dependencies:

- C++ Compiler
- Boost C++ Libraries
- [tls]

## Usage

The server listens for incoming connections on a specified port (default is 1234). Clients can connect to the server and participate in the game. The server handles game logic and communication with clients.

To stop the server, use `Ctrl+C`.

## Code Structure

The code is organized as follows:

- `main.cpp`: Entry point of the server, sets up the game and server controllers.
- `ServerController.hpp/cpp`: Implementation of the RType game server controller.
- `AsioWrapper.hpp/cpp`: Wrapper for Boost.Asio functionality, handles asynchronous UDP communication.
- `GameController.hpp/cpp`: Implementation of the RType game controller using ECS architecture.
