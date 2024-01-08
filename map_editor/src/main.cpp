#include "Renderer.hpp"
#define RAYGUI_IMPLEMENTATION
#define MAX_GESTURE_STRINGS   20
#include "raygui.h"
#include <iostream>
#include <string>

int main()
{
    const int screenWidth = 1500;
    const int screenHeight = 800;
    int segments = 0;
    std::shared_ptr<RL::IWindow> window = std::make_shared<RL::ZWindow>(screenWidth, screenHeight, "map editor");

    Vector2 touchPosition = { 0, 0 };
    Rectangle touchArea = { 1225, 0, screenWidth - 500, screenHeight};
    int gesturesCount = 0;
    char gestureStrings[MAX_GESTURE_STRINGS][32];
    int currentGesture = GESTURE_NONE;
    int lastGesture = GESTURE_NONE;

    RL::Utils::setTargetFPS(60);
    while (!window->shouldClose()) {

        lastGesture = currentGesture;
        currentGesture = GetGestureDetected();
        touchPosition = GetTouchPosition(0);

        if (CheckCollisionPointRec(touchPosition, touchArea) && (currentGesture != GESTURE_NONE)) {
            if (currentGesture != lastGesture) {
                switch (currentGesture) {
                    case GESTURE_TAP: TextCopy(gestureStrings[gesturesCount], "GESTURE TAP"); break;
                    case GESTURE_HOLD: TextCopy(gestureStrings[gesturesCount], "GESTURE HOLD"); break;
                    case GESTURE_DRAG: TextCopy(gestureStrings[gesturesCount], "GESTURE DRAG"); break;
                    default: break;
                }
                gesturesCount++;

                // Reset gestures strings
                if (gesturesCount >= MAX_GESTURE_STRINGS) {
                    for (auto & gestureString : gestureStrings) TextCopy(gestureString, "\0");
                    gesturesCount = 0;
                }
            }
        }






        window->beginDrawing();

        window->clearBackground(LIGHTGRAY);
        window->drawLine(1200, 0, 1200, GetScreenHeight(), Fade(BLACK, 0.6f));
        window->drawRectangle(1200, 0, GetScreenWidth() - 500, GetScreenHeight(), Fade(WHITE, 0.3f)); // zone d'entité à droite
        window->drawRectangle(50, 50, GetScreenWidth() - 400, GetScreenHeight() - 250, Fade(WHITE, 0.3f)); // content windows

        Rectangle scrollBarRect = { 50, 625, 1100, 20 };
        GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE, 64);
        segments = GuiScrollBar(scrollBarRect, segments, 0, 100);
        window->drawRectangle(scrollBarRect.x - 5, scrollBarRect.y - 5, scrollBarRect.width + 10, scrollBarRect.height + 10, Fade(BLACK, 0.3f));




        window->drawText("current gestures: ", 500, 250, 30, GRAY);
        window->drawText(gestureStrings[gesturesCount - 1], 500, 300, 30, GRAY);
        window->drawText("touche position:", 500, 370, 30, GRAY);
        window->drawText(std::to_string(static_cast<int>(touchPosition.x)), 500, 400, 30, GRAY);
        window->drawText(std::to_string(static_cast<int>(touchPosition.y)), 500, 430, 30, GRAY);


        if (currentGesture != GESTURE_NONE) { // Draw gestures
            DrawCircleV(touchPosition, 30, MAROON);
        }






        std::cout << "scrollbar: " << segments << std::endl;
        window->drawFPS(10, 10);
        window->endDrawing();
    }
    CloseWindow();

    return 0;
}
