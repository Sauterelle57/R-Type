cmake_minimum_required(VERSION 3.0)

project(MyProject)

# Client
add_executable(ClientExecutable
    client/main.cpp
)

# Server
add_executable(ServerExecutable
    server/main.cpp
)
