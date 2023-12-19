#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

    namespace rt
    {
        enum protocolType
        {
            // Server Part Server => Client
            PING,
            CONNECTION_REQUEST,
            MOVE,
            SHOOT,

            // Client Part Client => Server
            CONNECTION_ACCEPTED,
            CONNECTION_REFUSED,
            EVENT
        };

        enum eventType
        {
            // Server Part Server => Client
            PLAYER_CONNECTED,
            PLAYER_DISCONNECTED,
            PLAYER_MOVED,
            PLAYER_SHOOTED
        };

        struct Protocol
        {
            protocolType id;
            
            eventType event;

        };
    }

#endif /* !PROTOCOL_HPP_ */