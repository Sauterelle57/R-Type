#include "Renderer.hpp"
#define RAYGUI_IMPLEMENTATION
#define MAX_GESTURE_STRINGS   20
#include "raygui.h"
#include <iostream>
#include <string>
#include <vector>

struct Element {
    std::shared_ptr<RL::ITexture> texture;
    bool isSelected = false;
};

struct Object {
    std::shared_ptr<RL::ITexture> texture;
    tls::Vec3 position;
};

std::vector<Element> set_elements()
{
    std::vector<Element> elements;

    elements.push_back({
        .texture = std::make_shared<RL::ZTexture>("./map_editor/ressource/image_six.png"),
    });
    elements.push_back({
       .texture = std::make_shared<RL::ZTexture>("./map_editor/ressource/image_six.png"),
   });
    elements.push_back({
       .texture = std::make_shared<RL::ZTexture>("./map_editor/ressource/image_six.png"),
   });
    elements.push_back({
       .texture = std::make_shared<RL::ZTexture>("./map_editor/ressource/image_six.png"),
   });
    elements.push_back({
       .texture = std::make_shared<RL::ZTexture>("./map_editor/ressource/image_six.png"),
   });

    return elements;
}

void draw_structure(const std::shared_ptr<RL::IWindow>& window)
{
    window->drawLine(1300, 0, 1300, window->getScreenHeight(), RL::Utils::fade(BLACK, 0.6f));
    window->drawRectangle(1300, 0, window->getScreenWidth() - 500, window->getScreenHeight(), RL::Utils::fade(WHITE, 0.3f)); // zone d'entité à droite
    window->drawRectangle(50, 50, window->getScreenWidth() - 400, window->getScreenHeight() - 250, RL::Utils::fade(WHITE, 0.3f)); // content windows
}

void drawSidebardElements(const std::vector<Element>& elements) {
    unsigned int i = 0;
    for (auto & element : elements) {
        if (i % 2 == 0) {
            element.texture->drawEx({1350 - 12.5, static_cast<float>(50 + ((i / 2) * 120))}, 0, 0.50, WHITE);
        } else {
            element.texture->drawEx({1475 - 12.5, static_cast<float>(50 + ((i / 2)* 120))}, 0, 0.50, WHITE);
        }
        i++;
    }
}

int HandleScrollBar(Rectangle& scrollBarRect, int& segments)
{
    GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE, 64);
    segments = GuiScrollBar(scrollBarRect, segments, 0, 100);
    DrawRectangle(scrollBarRect.x - 5, scrollBarRect.y - 5, scrollBarRect.width + 10, scrollBarRect.height + 10, Fade(BLACK, 0.3f));
    return segments;
}



int main()
{
    // INIT WINDOW
    const int screenWidth = 1600;
    const int screenHeight = 900;
    int segments = 0;
    std::shared_ptr<RL::IWindow> window = std::make_shared<RL::ZWindow>(screenWidth, screenHeight, "map editor");

    // INIT GESTURE
    Vector2 touchPosition = { 0, 0 };
    Rectangle touchArea = { 1300, 0, screenWidth - 500, screenHeight};
    int gesturesCount = 0;
    char gestureStrings[MAX_GESTURE_STRINGS][32];
    int currentGesture = GESTURE_NONE;
    int lastGesture = GESTURE_NONE;

    bool drag = false;

    // INIT ENTITY
    std::vector<Element> elements = set_elements();

    std::vector<Object> objects;
    objects.push_back({
        .texture = std::make_shared<RL::ZTexture>("./map_editor/ressource/image_six.png"),
        .position = {500, 400, 0}
    });


    RL::Utils::setTargetFPS(60);
    while (!window->shouldClose()) {
        window->beginDrawing();

        // GESTURE
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

        // DRAW STRUCTURE
        window->clearBackground(LIGHTGRAY);
        draw_structure(window);

        // DRAW SCROLL
        Rectangle scrollBarRect = {55, 725, 1190, 20};
        segments = HandleScrollBar(scrollBarRect, segments);

        //DRAW OBJECTS
        for (auto & object : objects) {
            object.texture->drawEx({static_cast<float>(object.position._x),
                                    static_cast<float>(object.position._y)}, 0, 0.50, WHITE);
        }

        drawSidebardElements(elements);

        // DRAW GESTURE
        window->drawText("current gestures: ", 500, 250, 30, GRAY);
        window->drawText(gestureStrings[gesturesCount - 1], 500, 300, 30, GRAY);
        window->drawText("touche position:", 500, 370, 30, GRAY);
        window->drawText(std::to_string(static_cast<int>(touchPosition.x)), 500, 400, 30, GRAY);
        window->drawText(std::to_string(static_cast<int>(touchPosition.y)), 500, 430, 30, GRAY);

        if (currentGesture == GESTURE_TAP && CheckCollisionPointRec(touchPosition, touchArea)) { // Draw gestures
            drag = true;
        }
        if (currentGesture == GESTURE_NONE) {
            drag = false;
        }
        if (drag) {
            window->drawCircleV(touchPosition, 30, MAROON);
        }

        if (lastGesture == GESTURE_DRAG && currentGesture == GESTURE_NONE && !CheckCollisionPointRec(touchPosition, touchArea)) {
            std::cout << "drag" << std::endl;
            window->drawCircleV(touchPosition, 30, MAROON);
        }


        window->drawFPS(10, 10);
        window->endDrawing();
    }

    return 0;
}
