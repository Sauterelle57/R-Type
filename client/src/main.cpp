#include <cstdlib>
#include <random>
#include <memory>
#include "raylib.h"
#include "raymath.h"
#include "renderer/Window.hpp"
#include "renderer/ICamera.hpp"
#include "renderer/Camera.hpp"
#include "renderer/renderer.hpp"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include "DrawModel.hpp"
#include "Coordinator.hpp"
#include "Move.hpp"
#include "Core.hpp"

int main(void)
{
    std::unique_ptr<RT::Core> core = std::make_unique<RT::Core>();
    core->loop();
    return 0;
}
