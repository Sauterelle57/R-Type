#include <memory>
#include "raylib.h"

#include "Core.hpp"

int main(void)
{
    std::unique_ptr<RT::Core> core = std::make_unique<RT::Core>();
    core->loop();
    return 0;
}
