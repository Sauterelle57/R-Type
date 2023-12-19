/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Image.hpp
*/

#ifndef raylib_IMAGE_HPP
#define raylib_IMAGE_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IImage.hpp"

namespace RL {

    class ZImage : public IImage {
        public:
            ZImage() {
                _image = std::make_shared<Image>(LoadImageFromScreen());
            };

            ~ZImage() {
                UnloadImage(*_image);
            };

            ZImage(const std::string &fileName) {
                _image = std::make_shared<Image>(LoadImage(fileName.c_str()));
            };

            ZImage(const std::string &fileName, int width, int height, int format, int headerSize) {
                _image = std::make_shared<Image>(LoadImageRaw(fileName.c_str(), width, height, format, headerSize));
            };

            ZImage(const std::string &fileName, int *frames) {
                _image = std::make_shared<Image>(LoadImageAnim(fileName.c_str(), frames));
            };

            ZImage(Texture2D texture) {
                _image = std::make_shared<Image>(LoadImageFromTexture(texture));
            };

            ZImage(int width, int height, Color color) {
                _image = std::make_shared<Image>(GenImageColor(width, height, color));
            };

            ZImage(int width, int height, float density, Color inner, Color outer) {
                _image = std::make_shared<Image>(GenImageGradientRadial(width, height, density, inner, outer));
            };

            ZImage(int width, int height, int checksX, int checksY, Color col1, Color col2) {
                _image = std::make_shared<Image>(GenImageChecked(width, height, checksX, checksY, col1, col2));
            };

            ZImage(int width, int height, float factor) {
                _image = std::make_shared<Image>(GenImageWhiteNoise(width, height, factor));
            };

            ZImage(int width, int height, int offsetX, int offsetY, float scale) {
                _image = std::make_shared<Image>(GenImagePerlinNoise(width, height, offsetX, offsetY, scale));
            };

            ZImage(int width, int height, int tileSize) {
                _image = std::make_shared<Image>(GenImageCellular(width, height, tileSize));
            };

            ZImage(int width, int height, const std::string &text) {
                _image = std::make_shared<Image>(GenImageText(width, height, text.c_str()));
            };

            ZImage(Image image) {
                _image = std::make_shared<Image>(ImageCopy(image));
            };

            ZImage(Image image, Rectangle rec) {
                _image = std::make_shared<Image>(ImageFromImage(image, rec));
            };

            ZImage(const std::string &text, int fontSize, Color color) {
                _image = std::make_shared<Image>(ImageText(text.c_str(), fontSize, color));
            };

            ZImage(Font font, const std::string &text, float fontSize, float spacing, Color tint) {
                _image = std::make_shared<Image>(ImageTextEx(font, text.c_str(), fontSize, spacing, tint));
            };

            bool isReady() {
                return IsImageReady(*_image);
            };

            bool exportImage(const std::string &fileName) {
                return ExportImage(*_image, fileName.c_str());
            };

            bool exportAsCode(const std::string &fileName) {
                return ExportImageAsCode(*_image, fileName.c_str());
            };

            void format(int newFormat) {
                return ImageFormat(_image.get(), newFormat);
            };

            void toPOT(Color fill) {
                return ImageToPOT(_image.get(), fill);
            };

            void crop(Rectangle crop) {
                return ImageCrop(_image.get(), crop);
            };

            void alphaCrop(float threshold) {
                return ImageAlphaCrop(_image.get(), threshold);
            };

            void alphaClear(Color color, float threshold) {
                return ImageAlphaClear(_image.get(), color, threshold);
            };

            void alphaMask(Image alphaMask) {
                return ImageAlphaMask(_image.get(), alphaMask);
            };

            void alphaPremultiply() {
                return ImageAlphaPremultiply(_image.get());
            };

            void blurGaussian(int blurSize) {
                return ImageBlurGaussian(_image.get(), blurSize);
            };

            void resize(int newWidth, int newHeight) {
                return ImageResize(_image.get(), newWidth, newHeight);
            };

            void resizeNN(int newWidth,int newHeight) {
                return ImageResizeNN(_image.get(), newWidth, newHeight);
            };

            void resizeCanvas(int newWidth, int newHeight, int offsetX, int offsetY, Color fill) {
                return ImageResizeCanvas(_image.get(), newWidth, newHeight, offsetX, offsetY, fill);
            };

            void mipmaps() {
                return ImageMipmaps(_image.get());
            };

            void dither(int rBpp, int gBpp, int bBpp, int aBpp) {
                return ImageDither(_image.get(), rBpp, gBpp, bBpp, aBpp);
            };

            void flipVertical() {
                return ImageFlipVertical(_image.get());
            };

            void flipHorizontal() {
                return ImageFlipHorizontal(_image.get());
            };

            void rotateCW() {
                return ImageRotateCW(_image.get());
            };

            void rotateCCW() {
                return ImageRotateCCW(_image.get());
            };

            void colorTint(Color color) {
                return ImageColorTint(_image.get(), color);
            };

            void colorInvert() {
                return ImageColorInvert(_image.get());
            };

            void colorGrayscale() {
                return ImageColorGrayscale(_image.get());
            };

            void colorContrast(float contrast) {
                return ImageColorContrast(_image.get(), contrast);
            };

            void colorBrightness(int brightness) {
                return ImageColorBrightness(_image.get(), brightness);
            };

            void colorReplace(Color color, Color replace) {
                return ImageColorReplace(_image.get(), color, replace);
            };

            Color *color1oadColors() {
                return LoadImageColors(*_image);
            };

            Color *loadPalette(int maxPaletteSize, int *colorCount) {
                return LoadImagePalette(*_image, maxPaletteSize, colorCount);
            };

            void unloadColors(Color *colors) {
                return UnloadImageColors(colors);
            };

            void unloadPalette(Color *colors) {
                return UnloadImagePalette(colors);
            };

            Rectangle getAlphaBorder(float threshold) {
                return GetImageAlphaBorder(*_image, threshold);
            };

            Color getColor(int x, int y) {
                return GetImageColor(*_image, x, y);
            };

            void clearBackground(Color color) {
                return ImageClearBackground(_image.get(), color);
            };

            void drawPixel(int posX, int posY, Color color) {
                return ImageDrawPixel(_image.get(), posX, posY, color);
            };

            void drawPixelV(Vector2 position, Color color) {
                return ImageDrawPixelV(_image.get(), position, color);
            };

            void drawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
                return ImageDrawLine(_image.get(), startPosX, startPosY, endPosX, endPosY, color);
            };

            void drawLineV(Vector2 start, Vector2 end, Color color) {
                return ImageDrawLineV(_image.get(), start, end, color);
            };

            void drawCircle(int centerX, int centerY, int radius, Color color) {
                return ImageDrawCircle(_image.get(), centerX, centerY, radius, color);
            };

            void drawCircleV(Vector2 center, int radius, Color color) {
                return ImageDrawCircleV(_image.get(), center, radius, color);
            };

            void drawCircleLines(int centerX, int centerY, int radius, Color color) {
                return ImageDrawCircleLines(_image.get(), centerX, centerY, radius, color);
            };

            void drawCircleLinesV(Vector2 center, int radius, Color color) {
                return ImageDrawCircleLinesV(_image.get(), center, radius, color);
            };

            void drawRectangle(int posX, int posY, int width, int height, Color color) {
                return ImageDrawRectangle(_image.get(), posX, posY, width, height, color);
            };

            void drawRectangleV(Vector2 position, Vector2 size, Color color) {
                return ImageDrawRectangleV(_image.get(), position, size, color);
            };

            void drawRectangleRec(Rectangle rec, Color color) {
                return ImageDrawRectangleRec(_image.get(), rec, color);
            };

            void drawRectangleLines(Rectangle rec, int thick, Color color) {
                return ImageDrawRectangleLines(_image.get(), rec, thick, color);
            };

            void draw(Image src, Rectangle srcRec, Rectangle dstRec, Color tint) {
                return ImageDraw(_image.get(), src, srcRec, dstRec, tint);
            };

            void drawText(const std::string &text, int posX, int posY, int fontSize, Color color) {
                return ImageDrawText(_image.get(), text.c_str(), posX, posY, fontSize, color);
            };

            void drawTextEx(Font font, const std::string &text, Vector2 position, float fontSize, float spacing, Color tint) {
                return ImageDrawTextEx(_image.get(), font, text.c_str(), position, fontSize, spacing, tint);
            };

            std::shared_ptr<Image> getImage() const {
                return _image;
            }

            std::shared_ptr<Image> _image;

    };

} // RL

#endif //raylib_IMAGE_HPP
