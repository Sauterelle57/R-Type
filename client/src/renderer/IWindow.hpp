/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** IWindow.hpp
*/

#ifndef ZAPPY_GUI_IWINDOW_HPP
#define ZAPPY_GUI_IWINDOW_HPP

#include <iostream>
#include "raylib.h"

struct Image;
struct Vector2;
struct Vector3;
struct Camera3D;
struct Camera2D;
struct Color;
struct Rectangle;
struct Font;

namespace ZappyGui {

    class IWindow {
        public:
            virtual ~IWindow() = default;
            virtual bool shouldClose() = 0;
            virtual bool isReady() = 0;
            virtual bool isFullscreen() = 0;
            virtual bool isHidden() = 0;
            virtual bool isMinimized() = 0;
            virtual bool isMaximized() = 0;
            virtual bool isFocused() = 0;
            virtual bool isResized() = 0;
            virtual bool isState(unsigned int flag) = 0;
            virtual void setState(unsigned int flags) = 0;
            virtual void clearState(unsigned int flags) = 0;
            virtual void toggleFullscreen() = 0;
            virtual void maximize() = 0;
            virtual void minimize() = 0;
            virtual void restore() = 0;
            virtual void setIcon(Image image) = 0;
            virtual void setIcons(Image *images, int count) = 0;
            virtual void setTitle(const std::string &title) = 0;
            virtual void setPosition(int x, int y) = 0;
            virtual void setMonitor(int monitor) = 0;
            virtual void setMinSize(int width, int height) = 0;
            virtual void setSize(int width, int height) = 0;
            virtual void setOpacity(float opacity) = 0;
            virtual void *getHandle() = 0;
            virtual Vector2 getPosition() = 0;
            virtual Vector2 getScaleDPI() = 0;
            virtual int getScreenWidth() = 0;
            virtual int getScreenHeight() = 0;
            virtual int getRenderWidth() = 0;
            virtual int getRenderHeight() = 0;
            virtual int getMonitorCount() = 0;
            virtual int getCurrentMonitor() = 0;
            virtual Vector2 getMonitorPosition(int monitor) = 0;
            virtual int getMonitorWidth(int monitor) = 0;
            virtual int getMonitorHeight(int monitor) = 0;
            virtual int getMonitorPhysicalWidth(int monitor) = 0;
            virtual int getMonitorPhysicalHeight(int monitor) = 0;
            virtual int getMonitorRefreshRate(int monitor) = 0;
            virtual const std::string getMonitorName(int monitor) = 0;
            virtual void swapScreenBuffer() = 0;
            virtual Vector2 getWorldToScreen(Vector3 position, Camera camera) = 0;
            virtual Vector2 getScreenToWorld2D(Vector2 position, Camera2D camera) = 0;
            virtual Vector2 getWorldToScreenEx(Vector3 position, Camera camera, int width, int height) = 0;
            virtual Vector2 getWorldToScreen2D(Vector2 position, Camera2D camera) = 0;
            virtual void beginDrawing() = 0;
            virtual void endDrawing() = 0;
            virtual void clearBackground(Color color) = 0;
            virtual void takeScreenshot(const std::string &fileName) = 0;
            virtual void drawPixel(int posX, int posY, Color color) = 0;
            virtual void drawPixelV(Vector2 position, Color color) = 0;
            virtual void drawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) = 0;
            virtual void drawLineV(Vector2 startPos, Vector2 endPos, Color color) = 0;
            virtual void drawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color) = 0;
            virtual void drawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color) = 0;
            virtual void drawLineBezierQuad(Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thick, Color color) = 0;
            virtual void drawLineBezierCubic(Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thick, Color color) = 0;
            virtual void drawLineStrip(Vector2 *points, int pointCount, Color color) = 0;
            virtual void drawCircle(int centerX, int centerY, float radius, Color color) = 0;
            virtual void drawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) = 0;
            virtual void drawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) = 0;
            virtual void drawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2) = 0;
            virtual void drawCircleV(Vector2 center, float radius, Color color) = 0;
            virtual void drawCircleLines(int centerX, int centerY, float radius, Color color) = 0;
            virtual void drawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color) = 0;
            virtual void drawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color) = 0;
            virtual void drawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) = 0;
            virtual void drawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) = 0;
            virtual void drawRectangle(int posX, int posY, int width, int height, Color color) = 0;
            virtual void drawRectangleV(Vector2 position, Vector2 size, Color color) = 0;
            virtual void drawRectangleRec(Rectangle rec, Color color) = 0;
            virtual void drawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color) = 0;
            virtual void drawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2) = 0;
            virtual void drawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2) = 0;
            virtual void drawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4) = 0;
            virtual void drawRectangleLines(int posX, int posY, int width, int height, Color color) = 0;
            virtual void drawRectangleLinesEx(Rectangle rec, float lineThick, Color color) = 0;
            virtual void drawRectangleRounded(Rectangle rec, float roundness, int segments, Color color) = 0;
            virtual void drawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color) = 0;
            virtual void drawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color) = 0;
            virtual void drawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color) = 0;
            virtual void drawTriangleFan(Vector2 *points, int pointCount, Color color) = 0;
            virtual void drawTriangleStrip(Vector2 *points, int pointCount, Color color) = 0;
            virtual void drawPoly(Vector2 center, int sides, float radius, float rotation, Color color) = 0;
            virtual void drawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color) = 0;
            virtual void drawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color) = 0;
            virtual void drawFPS(int posX, int posY) = 0;
            virtual void drawText(const std::string &text, int posX, int posY, int fontSize, Color color) = 0;
            virtual void drawTextEx(Font font, const std::string &text, Vector2 position, float fontSize, float spacing, Color tint) = 0;
            virtual void drawTextPro(Font font, const std::string &text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint) = 0;
            virtual void drawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint) = 0;
            virtual void drawTextCodepoints(Font font, const int *codepoints, int count, Vector2 position, float fontSize, float spacing, Color tint) = 0;
            virtual void drawLine3D(Vector3 startPos, Vector3 endPos, Color color) = 0;
            virtual void drawPoint3D(Vector3 position, Color color) = 0;
            virtual void drawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color) = 0;
            virtual void drawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color) = 0;
            virtual void drawTriangleStrip3D(Vector3 *points, int pointCount, Color color) = 0;
            virtual void drawCube(Vector3 position, float width, float height, float length, Color color) = 0;
            virtual void drawCubeV(Vector3 position, Vector3 size, Color color) = 0;
            virtual void drawCubeWires(Vector3 position, float width, float height, float length, Color color) = 0;
            virtual void drawCubeWiresV(Vector3 position, Vector3 size, Color color) = 0;
            virtual void drawSphere(Vector3 centerPos, float radius, Color color) = 0;
            virtual void drawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color) = 0;
            virtual void drawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color) = 0;
            virtual void drawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color) = 0;
            virtual void drawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color) = 0;
            virtual void drawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color) = 0;
            virtual void drawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color) = 0;
            virtual void drawCapsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color) = 0;
            virtual void drawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color) = 0;
            virtual void drawPlane(Vector3 centerPos, Vector2 size, Color color) = 0;
            virtual void drawGrid(int slices, float spacing) = 0;
            virtual void drawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color) = 0;
            };

} // ZappyGui

#endif //ZAPPY_GUI_IWINDOW_HPP
