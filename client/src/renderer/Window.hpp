/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Window.hpp
*/

#ifndef raylib_WINDOW_HPP
#define raylib_WINDOW_HPP

#include <raylib.h>
#include <iostream>

#include "IWindow.hpp"
#include "rlgl.h"

namespace RL {

    class ZWindow : public IWindow {
        public:
            ZWindow(int width, int height, const std::string &title) {
                InitWindow(width, height, title.c_str());
            };

            ~ZWindow() {
                CloseWindow();
            };

            bool shouldClose() {
                return WindowShouldClose();
            };

            bool isReady() {
                return IsWindowReady();
            };

            bool isFullscreen() {
                return IsWindowFullscreen();
            };

            bool isHidden() {
                return IsWindowHidden();
            };

            bool isMinimized() {
                return IsWindowMinimized();
            };
            bool isMaximized() {
                return IsWindowMaximized();
            };

            bool isFocused() {
                return IsWindowFocused();
            };

            bool isResized() {
                return IsWindowResized();
            };

            bool isState(unsigned int flag) {
                return IsWindowState(flag);
            };

            void setState(unsigned int flags) {
                return SetWindowState(flags);
            };

            void clearState(unsigned int flags) {
                return ClearWindowState(flags);
            };

            void toggleFullscreen() {
                return ToggleFullscreen();
            };

            void maximize() {
                return MaximizeWindow();
            };

            void minimize() {
                return MinimizeWindow();
            };

            void restore() {
                return RestoreWindow();
            };

            void setIcon(Image image) {
                return SetWindowIcon(image);
            };

            void setIcons(Image *images, int count) {
                return SetWindowIcons(images, count);
            };

            void setTitle(const std::string &title) {
                return SetWindowTitle(title.c_str());
            };

            void setPosition(int x, int y) {
                return SetWindowPosition(x, y);
            };

            void setMonitor(int monitor) {
                return SetWindowMonitor(monitor);
            };

            void setMinSize(int width, int height) {
                return SetWindowMinSize(width, height);
            };

            void setSize(int width, int height) {
                return SetWindowSize(width, height);
            };

            void setOpacity(float opacity) {
                return SetWindowOpacity(opacity);
            };

            void *getHandle() {
                return GetWindowHandle();
            };

            Vector2 getPosition() {
                return GetWindowPosition();
            };

            Vector2 getScaleDPI() {
                return GetWindowScaleDPI();
            };
            int getScreenWidth() {
                return GetScreenWidth();
            };

            int getScreenHeight() {
                return GetScreenHeight();
            };

            int getRenderWidth() {
                return GetRenderWidth();
            };

            int getRenderHeight() {
                return GetRenderHeight();
            };

            int getMonitorCount() {
                return GetMonitorCount();
            };

            int getCurrentMonitor() {
                return GetCurrentMonitor();
            };

            Vector2 getMonitorPosition(int monitor) {
                return GetMonitorPosition(monitor);
            };

            int getMonitorWidth(int monitor) {
                return GetMonitorWidth(monitor);
            };

            int getMonitorHeight(int monitor) {
                return GetMonitorHeight(monitor);
            };

            int getMonitorPhysicalWidth(int monitor) {
                return GetMonitorPhysicalWidth(monitor);
            };

            int getMonitorPhysicalHeight(int monitor) {
                return GetMonitorPhysicalHeight(monitor);
            };

            int getMonitorRefreshRate(int monitor) {
                return GetMonitorRefreshRate(monitor);
            };

            const std::string getMonitorName(int monitor) {
                return GetMonitorName(monitor);
            };

            void swapScreenBuffer() {
                return SwapScreenBuffer();
            };

            Vector2 getWorldToScreen(Vector3 position, Camera camera) {
                return GetWorldToScreen(position, camera);
            };

            Vector2 getScreenToWorld2D(Vector2 position, Camera2D camera) {
                return GetScreenToWorld2D(position, camera);
            };

            Vector2 getWorldToScreenEx(Vector3 position, Camera camera, int width, int height) {
                return GetWorldToScreenEx(position, camera, width, height);
            };

            Vector2 getWorldToScreen2D(Vector2 position, Camera2D camera) {
                return GetWorldToScreen2D(position, camera);
            };

            void beginDrawing() {
                return BeginDrawing();
            };

            void endDrawing() {
                return EndDrawing();
            };

            void clearBackground(Color color) {
                return ClearBackground(color);
            };

            void takeScreenshot(const std::string &fileName) {
                return TakeScreenshot(fileName.c_str());
            };

            void drawPixel(int posX, int posY, Color color) {
                return DrawPixel(posX, posY, color);
            };

            void drawPixelV(Vector2 position, Color color) {
                return DrawPixelV(position, color);
            };

            void drawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
                return DrawLine(startPosX, startPosY, endPosX, endPosY, color);
            };

            void drawLineV(Vector2 startPos, Vector2 endPos, Color color) {
                return DrawLineV(startPos, endPos, color);
            };

            void drawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color) {
                return DrawLineEx(startPos, endPos, thick, color);
            };

            void drawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color) {
                return DrawLineBezier(startPos, endPos, thick, color);
            };

            // void drawLineBezierQuad(Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thick, Color color) {
            //     return DrawLineBezierQuad(startPos, endPos, controlPos, thick, color);
            // };

            // void drawLineBezierCubic(Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thick, Color color) {
            //     return DrawLineBezierCubic(startPos,  endPos,  startControlPos,  endControlPos, thick, color);
            // };

            void drawLineStrip(Vector2 *points, int pointCount, Color color) {
                return DrawLineStrip(points, pointCount, color);
            };

            void drawCircle(int centerX, int centerY, float radius, Color color) {
                return DrawCircle(centerX, centerY, radius, color);
            };

            void drawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) {
                return DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
            };

            void drawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) {
                return DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
            };

            void drawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2) {
                return DrawCircleGradient(centerX, centerY, radius, color1, color2);
            };

            void drawCircleV(Vector2 center, float radius, Color color) {
                return DrawCircleV(center, radius, color);
            };

            void drawCircleLines(int centerX, int centerY, float radius, Color color) {
                return DrawCircleLines(centerX, centerY, radius, color);
            };

            void drawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color) {
                return DrawEllipse(centerX, centerY, radiusH, radiusV, color);
            };

            void drawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color) {
                return DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
            };

            void drawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) {
                return DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
            };

            void drawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) {
                return DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
            };

            void drawRectangle(int posX, int posY, int width, int height, Color color) {
                return DrawRectangle(posX, posY, width, height, color);
            };

            void drawRectangleV(Vector2 position, Vector2 size, Color color) {
                return DrawRectangleV(position, size, color);
            };

            void drawRectangleRec(Rectangle rec, Color color) {
                return DrawRectangleRec(rec, color);
            };

            void drawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color) {
                return DrawRectanglePro(rec, origin, rotation, color);
            };

            void drawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2) {
                return DrawRectangleGradientV(posX, posY, width, height, color1, color2);
            };

            void drawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2) {
                return DrawRectangleGradientH(posX, posY, width, height, color1, color2);
            };

            void drawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4) {
                return DrawRectangleGradientEx(rec, col1, col2, col3, col4);
            };

            void drawRectangleLines(int posX, int posY, int width, int height, Color color) {
                return DrawRectangleLines(posX, posY, width, height, color);
            };

            void drawRectangleLinesEx(Rectangle rec, float lineThick, Color color) {
                return DrawRectangleLinesEx(rec, lineThick, color);
            };

            void drawRectangleRounded(Rectangle rec, float roundness, int segments, Color color) {
                return DrawRectangleRounded(rec, roundness, segments, color);
            };

            void drawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color) {
                return DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
            };

            void drawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
                return DrawTriangle(v1, v2, v3, color);
            };

            void drawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
                return DrawTriangleLines(v1, v2, v3, color);
            };

            void drawTriangleFan(Vector2 *points, int pointCount, Color color) {
                return DrawTriangleFan(points, pointCount, color);
            };

            void drawTriangleStrip(Vector2 *points, int pointCount, Color color) {
                return DrawTriangleStrip(points, pointCount, color);
            };

            void drawPoly(Vector2 center, int sides, float radius, float rotation, Color color) {
                return DrawPoly(center, sides, radius, rotation, color);
            };

            void drawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color) {
                return DrawPolyLines(center, sides, radius, rotation, color);
            };

            void drawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color) {
                return DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
            };

            void drawFPS(int posX, int posY) {
                return DrawFPS(posX, posY);
            };

            void drawText(const std::string &text, int posX, int posY, int fontSize, Color color) {
                return DrawText(text.c_str(), posX, posY, fontSize, color);
            };

            void drawTextEx(Font font, const std::string &text, Vector2 position, float fontSize, float spacing, Color tint) {
                return DrawTextEx(font, text.c_str(), position, fontSize, spacing, tint);
            };

            void drawTextPro(Font font, const std::string &text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint) {
                return DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, tint);
            };

            void drawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint) {
                return DrawTextCodepoint(font, codepoint, position, fontSize, tint);
            };

            void drawTextCodepoints(Font font, const int *codepoints, int count, Vector2 position, float fontSize, float spacing, Color tint) {
                return DrawTextCodepoints(font, codepoints, count, position, fontSize, spacing, tint);
            };

            void drawLine3D(Vector3 startPos, Vector3 endPos, Color color) {
                return DrawLine3D(startPos, endPos, color);
            };

            void drawPoint3D(Vector3 position, Color color) {
                return DrawPoint3D(position, color);
            };

            void drawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color) {
                return DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
            };

            void drawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color) {
                return DrawTriangle3D(v1, v2, v3, color);
            };

            void drawTriangleStrip3D(Vector3 *points, int pointCount, Color color) {
                return DrawTriangleStrip3D(points, pointCount, color);
            };

            void drawCube(Vector3 position, float width, float height, float length, Color color) {
                return DrawCube(position, width, height, length, color);
            };

            void drawCubeV(Vector3 position, Vector3 size, Color color) {
                return DrawCubeV(position, size, color);
            };

            void drawCubeWires(Vector3 position, float width, float height, float length, Color color) {
                return DrawCubeWires(position, width, height, length, color);
            };

            void drawCubeWiresV(Vector3 position, Vector3 size, Color color) {
                return DrawCubeWiresV(position, size, color);
            };

            void drawSphere(Vector3 centerPos, float radius, Color color) {
                return DrawSphere(centerPos, radius, color);
            };

            void drawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color) {
                return DrawSphereEx(centerPos, radius, rings, slices, color);
            };

            void drawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color) {
                return DrawSphereWires(centerPos, radius, rings, slices, color);
            };

            void drawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color) {
                return DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
            };

            void drawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color) {
                return DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
            };

            void drawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color) {
                return DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
            };

            void drawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color) {
                return DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);
            };

            void drawCapsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color) {
                return DrawCapsule(startPos, endPos, radius, slices, rings, color);
            };

            void drawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color) {
                return DrawCapsuleWires(startPos, endPos, radius, slices, rings, color);
            };

            void drawPlane(Vector3 centerPos, Vector2 size, Color color) {
                return DrawPlane(centerPos, size, color);
            };

            void drawGrid(int slices, float spacing) {
                return DrawGrid(slices, spacing);
            };

            void drawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color) {
                float x = position.x;
                float y = position.y;
                float z = position.z;

                rlSetTexture(texture.id);

                rlBegin(RL_QUADS);
                rlColor4ub(color.r, color.g, color.b, color.a);
                rlNormal3f(0.0f, 0.0f, 1.0f);
                rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);
                rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);
                rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);
                rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);
                rlNormal3f(0.0f, 0.0f, - 1.0f);
                rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);
                rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);
                rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);
                rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);
                rlNormal3f(0.0f, 1.0f, 0.0f);
                rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);
                rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);
                rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);
                rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);
                rlNormal3f(0.0f, - 1.0f, 0.0f);
                rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);
                rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);
                rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);
                rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);
                rlNormal3f(1.0f, 0.0f, 0.0f);
                rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);
                rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);
                rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);
                rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);
                rlNormal3f( - 1.0f, 0.0f, 0.0f);
                rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);
                rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);
                rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);
                rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);
                rlEnd();

                rlSetTexture(0);
            }
    };

} // RL

#endif //raylib_WINDOW_HPP
