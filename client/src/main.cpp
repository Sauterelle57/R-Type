/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ComponentsManager
*/

#include "raylib.h"
#include "renderer/Window.hpp"
#include "renderer/ICamera.hpp"
#include "renderer/Camera.hpp"
#include "renderer/renderer.hpp"
#include <math.h>
#include <memory>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    std::shared_ptr<ZappyGui::IWindow> window = std::make_shared<ZappyGui::ZWindow>(screenWidth, screenHeight, "R TYPE WINDOW");

    std::shared_ptr<ZappyGui::ICamera> camera = std::make_shared<ZappyGui::ZCamera>();
    camera->setPosition((Vector3){ 30.0f, 20.0f, 30.0f });
    camera->setTarget((Vector3){ 0.0f, 0.0f, 0.0f });      // Camera looking at point
    camera->setUp((Vector3){ 0.0f, 1.0f, 0.0f });          // Camera up vector (rotation towards target)
    camera->setFovy(70.0f);                                // Camera field-of-view Y
    camera->setProjection(CAMERA_PERSPECTIVE);             // Camera projection type

    // Specify the amount of blocks in each direction
    const int numBlocks = 15;

    ZappyGui::Utils::setTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window->shouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        double time = ZappyGui::Utils::getTime();

        float scale = (2.0f + (float)sin(time))*0.7f;

        // Move camera around the scene
        double cameraTime = time*0.3;
        camera->setPosition({(float) cos(cameraTime) * 40.0f, (float) sin(cameraTime) * 40.0f, camera->getPosition().z});
        window->beginDrawing();
        window->clearBackground(RAYWHITE);

        camera->beginMode();

        window->drawGrid(10, 5.0f);

        for (int x = 0; x < numBlocks; x++)
        {
            for (int y = 0; y < numBlocks; y++)
            {
                for (int z = 0; z < numBlocks; z++)
                {
                    // Scale of the blocks depends on x/y/z positions
                    float blockScale = (x + y + z)/30.0f;

                    // Scatter makes the waving effect by adding blockScale over time
                    float scatter = sinf(blockScale*20.0f + (float)(time*4.0f));

                    // Calculate the cube position
                    Vector3 cubePos = {
                            (float)(x - numBlocks/2)*(scale*3.0f) + scatter,
                            (float)(y - numBlocks/2)*(scale*2.0f) + scatter,
                            (float)(z - numBlocks/2)*(scale*3.0f) + scatter
                    };

                    // Pick a color with a hue depending on cube position for the rainbow color effect
                    Color cubeColor = ZappyGui::Utils::colorFromHSV((float)(((x + y + z)*18)%360), 0.75f, 0.9f);

                    // Calculate cube size
                    float cubeSize = (2.4f - scale)*blockScale;
                    window->drawCube(cubePos, cubeSize, cubeSize, cubeSize, cubeColor);
                }
            }
        }
        camera->endMode();
        window->drawFPS(10, 10);
        window->endDrawing();
    }
    return 0;
}