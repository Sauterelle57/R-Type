
#include "Renderer.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"                 // Required for GUI controls

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    std::shared_ptr<RL::IWindow> window = std::make_shared<RL::ZWindow>(screenWidth, screenHeight, "maman");

    float roundness = 0.2f;
    float width = 200.0f;
    float height = 100.0f;
    float segments = 0.0f;
    float lineThick = 1.0f;

    bool drawRect = false;
    bool drawRoundedRect = true;
    bool drawRoundedLines = false;

    RL::Utils::setTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window->shouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Rectangle rec = { ((float)GetScreenWidth() - width - 250)/2, (GetScreenHeight() - height)/2.0f, (float)width, (float)height };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        window->beginDrawing();

        window->clearBackground(RAYWHITE);

        window->drawLine(560, 0, 560, window->getScreenHeight(), RL::Utils::fade(LIGHTGRAY, 0.6f));
        window->drawRectangle(560, 0, window->getScreenWidth() - 500, window->getScreenHeight(), RL::Utils::fade(LIGHTGRAY, 0.3f));

        if (drawRect) window->drawRectangleRec(rec, RL::Utils::fade(GOLD, 0.6f));
        if (drawRoundedRect) window->drawRectangleRounded(rec, roundness, (int)segments, RL::Utils::fade(MAROON, 0.2f));
        if (drawRoundedLines) window->drawRectangleRoundedLines(rec, roundness, (int)segments, lineThick, RL::Utils::fade(MAROON, 0.4f));

        // Draw GUI controls
        //------------------------------------------------------------------------------
        GuiSliderBar({ 640, 40, 105, 20 }, "Width", NULL, &width, 0, static_cast<float>(window->getScreenWidth() - 300));
        GuiSliderBar({ 640, 70, 105, 20 }, "Height", NULL, &height, 0, static_cast<float>(window->getScreenHeight() - 50));
        GuiSliderBar({ 640, 140, 105, 20 }, "Roundness", NULL, &roundness, 0.0f, 1.0f);
        GuiSliderBar({ 640, 170, 105, 20 }, "Thickness", NULL, &lineThick, 0, 20);
        GuiSliderBar({ 640, 240, 105, 20}, "Segments", NULL, &segments, 0, 60);

        GuiCheckBox({ 640, 320, 20, 20 }, "DrawRoundedRect", &drawRoundedRect);
        GuiCheckBox({ 640, 350, 20, 20 }, "DrawRoundedLines", &drawRoundedLines);
        GuiCheckBox({ 640, 380, 20, 20}, "DrawRect", &drawRect);
        //------------------------------------------------------------------------------

        std::string mode = std::string("MODE: ") + ((segments >= 4)? "MANUAL" : "AUTO");

        window->drawText(mode, 640, 280, 10, (segments >= 4)? MAROON : DARKGRAY);

        window->drawFPS(10, 10);

        window->endDrawing();
        //----------------------------------------------------------------------------------
    }
    return 0;
}