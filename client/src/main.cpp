//#include <memory>
//#include "raylib.h"


//#include "Core.hpp"
//#include "renderer/Audio.hpp"
//#include <raylib.h>

//#include "IUdpClient.hpp"
#include "UdpClient.hpp"
//#include <thread>

int main(void)
{
    std::shared_ptr<std::queue<rt::ReceivedMessage>> receivedMessages = std::make_shared<std::queue<rt::ReceivedMessage>>();
    //rt::UdpClient udpClient("127.0.0.1", 1234, receivedMessages);

    return 0;
}