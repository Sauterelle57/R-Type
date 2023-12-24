```text
 ________                _________    ___    ___ ________  _______      
|\   __  \              |\___   ___\ |\  \  /  /|\   __  \|\  ___ \     
\ \  \|\  \  ___________\|___ \  \_| \ \  \/  / | \  \|\  \ \   __/|    
 \ \   _  _\|\____________\  \ \  \   \ \    / / \ \   ____\ \  \_|/__  
  \ \  \\  \\|____________|   \ \  \   \/  /  /   \ \  \___|\ \  \_|\ \ 
   \ \__\\ _\                  \ \__\__/  / /      \ \__\    \ \_______\
    \|__|\|__|                  \|__|\___/ /        \|__|     \|_______|
                                    \|___|/                             
                                                                        
                                                                        
```


# R-Type

1. [Introduction](#introduction)
2. [Installation](#installation)
    - [Cross-Platform Requirements](#cross-platform-requirements)
    - [Prerequisites](#prerequisites)
3. [Launch](#play)
4. [Rtype parts](#project)
5. [Contributors](#contributors)

## Introduction
The goal of this project is to implement a multithreaded  and a graphical  for a well-known legacy video game called R-Type, using a game engine of your own design .

Check our website at : https://marie-2.gitbook.io/rtype/

## Installation
The R-Type solution is designed to be cross-platform, supporting various operating systems. Follow the instructions below based on your platform of choice.

### Cross-Platform Requirements

- **Platform Independence:** The R-Type solution is built to be platform-independent. Ensure that you have a compatible system, including Windows and Linux distributions.

### Prerequisites

Before installing the R-Type solution, make sure you have the following prerequisites installed on your system:

- **[C++]:** Have C++ installed (On Windows and Linux) (minimum version C++ 20)
- **[Cmake]:** Cmake must be installed on your host (minimun version 3.26).
- **[VCPKG]** VCPKG must be installed & correctly configured on Windows.
    - VCPKG must be installed on your host directory like C:/Users/YOUR_USER/vcpkg
    - Set vcpkg path in your environment variable.

## Installation

Follow these general steps to install the R-Type solution:

1. Clone the repository to your local machine:

    ```bash
    git clone git@github.com:EpitechPromo2026/B-CPP-500-STG-5-2-rtype-noah.gosciniak.git
    ```

2. Navigate to the project directory:

    ```bash
    cd B-CPP-500-STG-5-2-rtype-noah.gosciniak.git
    ```

3. Install requirements to build rtype [ONLY FOR WINDOWS]

    ```bash
    .\install-windows.bat
    ```

4. Install requirements to build rtype [ONLY FOR LINUX]
    
    For (apt) package manager : 
    ```bash
    ./install-apt.sh
    ```

    For (dnf) package manager :
    ```bash
    ./install-dnf.sh
    ```

5. Build the rtype solution
    
    On Windows :
    ```
    .\prepare.bat
    ```

    On Linux :
    ```bash
    ./prepare.sh
    ```

## Play 

Launch the server
```
./rtype_server
```

Launch the client
```
./rtype_client
```

## Project

- [Server](./server/README.md)  
- [Client](./client/README.md)  
- [Protocol](.protocol/Protocol.md) 

## Contributors

Axel Lievre - [Github] - axel.lievre@epitech.eu  
Noah Gosciniak - [Github] - noah.gosciniak@epitech.eu  
Marie Giacomel - [GitHub] - marie.giacomel@epitech.eu  
Lucas Hoch - [GitHub] - lucas.hoch@epitech.eu  
Quentin Erdinger - [GitHub] - quentin.erdinger@epitech.eu  