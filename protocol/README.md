# R-Type Protocol RFC

## 1. Introduction

This document specifies the communication protocol for the R-Type project. The protocol enables clients to communicate with the server by sending commands and receiving responses. Commands are structured with specific arguments, and possible responses are defined for each command.

## 2. Client to Server Command Format

### 2.1 Command Details

#### 2.1.1 PING

- **Arguments:** None.
- **Possible Responses:** "OK"

#### 2.1.2 CONNECTION_REQUEST

- **Arguments:** None.
- **Possible Responses:** "CONNECTION_ACCEPTED {ID}" <br/> "CONNECTION_REFUSED"

#### 2.1.3 DISCONNECT

- **Arguments:** None.
- **Possible Responses:** None.

#### 2.1.4 MOVE

- **Arguments:** 
  - X: Horizontal axis vector
  - Y: Vertical axis vector
  - Z: Depth vector
- **Possible Responses:** None.

**Examples of MOVE command:**
- `MOVE 1 0 0`: Move right
- `MOVE -1 0 0`: Move left
- `MOVE 0 -1 0`: Move down
- `MOVE 0 1 0`: Move up
- `MOVE 0 0 -1`: Move backward (depth)
- `MOVE 0 0 1`: Move forward (depth)

#### 2.1.5 SHOOT

- **Arguments:** None.
- **Possible Responses:** None.

## 3. Server to Client Command

### 3.1 Get Map

The "Get Map" event is used to obtain information about entities present on the map.


```cpp
The client will receive : std::vector<Entity>

struct Entity
    {
        std::uint32_t ECSEntity;

        std::bitset<15> signature;

        tls::Vec3 position;
        tls::Vec4 rotation;
        tls::Vec3 scale;
        ENTITY_TYPE entityType;
        tls::BoundingBox bounds;
    };
```
