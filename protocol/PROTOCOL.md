# R-Type Protocol

## Protocol (Client => Server)

| COMMAND            | ARGS      | RESULT |
| ------------------ | --------- | ------ |
| CONNECTION_REQUEST | []        | []     |
| PING               | []        | "OK"   |
| MOVE               | [x y z]   | []     |
| SHOOT              | []        | []     |

## Protocol Event (Server => Client)

1. Display / update entity
    ```text
    "[ID] TRANSFORM [PX] [PY] [PZ] [RX] [RY] [RZ] [RA] [SX] [SY] [SZ] [TYPE]"

    ID: ECS's ID
    PX, PY, PZ: Entity position
    RX, RY, RZ, RA: Entity rotation
    SX, SY, SZ: Entity scale
    TYPE: Entity type (ex: PLAYER, ENEMY, ...)
    ```

2. Destroy entity
    ```text
    "[ID] DESTROY"

    ID: ECS's ID
    ```
