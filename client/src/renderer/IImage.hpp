/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IImage.hpp
*/

#ifndef raylib_IIMAGE_HPP
#define raylib_IIMAGE_HPP

#include <iostream>

struct Image;
struct Color;
struct Rectangle;
struct Vector2;
struct Font;

namespace RL {

    class IImage {
        public:
            virtual ~IImage() = default;
            virtual bool isReady() = 0;
            virtual bool exportImage(const std::string &fileName) = 0;
            virtual bool exportAsCode(const std::string &fileName) = 0;
            virtual void format(int newFormat) = 0;
            virtual void toPOT(Color fill) = 0;
            virtual void crop(Rectangle crop) = 0;
            virtual void alphaCrop(float threshold) = 0;
            virtual void alphaClear(Color color, float threshold) = 0;
            virtual void alphaMask(Image alphaMask) = 0;
            virtual void alphaPremultiply() = 0;
            virtual void blurGaussian(int blurSize) = 0;
            virtual void resize(int newWidth, int newHeight) = 0;
            virtual void resizeNN(int newWidth,int newHeight) = 0;
            virtual void resizeCanvas(int newWidth, int newHeight, int offsetX, int offsetY, Color fill) = 0;
            virtual void mipmaps() = 0;
            virtual void dither(int rBpp, int gBpp, int bBpp, int aBpp) = 0;
            virtual void flipVertical() = 0;
            virtual void flipHorizontal() = 0;
            virtual void rotateCW() = 0;
            virtual void rotateCCW() = 0;
            virtual void colorTint(Color color) = 0;
            virtual void colorInvert() = 0;
            virtual void colorGrayscale() = 0;
            virtual void colorContrast(float contrast) = 0;
            virtual void colorBrightness(int brightness) = 0;
            virtual void colorReplace(Color color, Color replace) = 0;
            virtual Color *color1oadColors() = 0;
            virtual Color *loadPalette(int maxPaletteSize, int *colorCount) = 0;
            virtual void unloadColors(Color *colors) = 0;
            virtual void unloadPalette(Color *colors) = 0;
            virtual Rectangle getAlphaBorder(float threshold) = 0;
            virtual Color getColor(int x, int y) = 0;
            virtual void clearBackground(Color color) = 0;
            virtual void drawPixel(int posX, int posY, Color color) = 0;
            virtual void drawPixelV(Vector2 position, Color color) = 0;
            virtual void drawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) = 0;
            virtual void drawLineV(Vector2 start, Vector2 end, Color color) = 0;
            virtual void drawCircle(int centerX, int centerY, int radius, Color color) = 0;
            virtual void drawCircleV(Vector2 center, int radius, Color color) = 0;
            virtual void drawCircleLines(int centerX, int centerY, int radius, Color color) = 0;
            virtual void drawCircleLinesV(Vector2 center, int radius, Color color) = 0;
            virtual void drawRectangle(int posX, int posY, int width, int height, Color color) = 0;
            virtual void drawRectangleV(Vector2 position, Vector2 size, Color color) = 0;
            virtual void drawRectangleRec(Rectangle rec, Color color) = 0;
            virtual void drawRectangleLines(Rectangle rec, int thick, Color color) = 0;
            virtual void draw(Image src, Rectangle srcRec, Rectangle dstRec, Color tint) = 0;
            virtual void drawText(const std::string &text, int posX, int posY, int fontSize, Color color) = 0;
            virtual void drawTextEx(Font font, const std::string &text, Vector2 position, float fontSize, float spacing, Color tint) = 0;
            virtual std::shared_ptr<Image> getImage() const = 0;
            };

} // RL

#endif //raylib_IIMAGE_HPP
