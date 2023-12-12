/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Font.hpp
*/

#ifndef ZAPPY_GUI_FONT_HPP
#define ZAPPY_GUI_FONT_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IFont.hpp"

namespace ZappyGui {

    class ZFont : public IFont {
        public:
            ZFont() {
                _font = std::make_unique<Font>(GetFontDefault());
            };

            ~ZFont() {
                UnloadFont(*_font);
            };

            void load(const std::string &fileName) {
                _font = std::make_unique<Font>(LoadFont(fileName.c_str()));
            };

            void loadEx(const std::string &fileName, int fontSize, int *fontChars, int glyphCount) {
                _font = std::make_unique<Font>(LoadFontEx(fileName.c_str(), fontSize, fontChars, glyphCount));
            };

            void loadFromImage(Image image, Color key, int firstChar) {
                _font = std::make_unique<Font>(LoadFontFromImage(image, key, firstChar));
            };

            bool isReady() {
                return IsFontReady(*_font);
            };

            GlyphInfo *loadData(unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int glyphCount, int type) {
                return LoadFontData(fileData, dataSize, fontSize, fontChars, glyphCount, type);
            };

            Image genImageAtlas(const GlyphInfo *chars, Rectangle **recs, int glyphCount, int fontSize, int padding, int packMethod) {
                return GenImageFontAtlas(chars, recs, glyphCount, fontSize, padding, packMethod);
            };

            void unloadData(GlyphInfo *chars, int glyphCount) {
                return UnloadFontData(chars,glyphCount);
            };

            bool exportAsCode(const std::string &fileName) {
                return ExportFontAsCode(*_font, fileName.c_str());
            };

            Vector2 measureTextEx(const std::string &text, float fontSize, float spacing) {
                return MeasureTextEx(*_font, text.c_str(), fontSize, spacing);
            };

            int getGlyphIndex(int codepoint) {
                return GetGlyphIndex(*_font, codepoint);
            };

            GlyphInfo getGlyphInfo(int codepoint) {
                return GetGlyphInfo(*_font, codepoint);
            };

            Rectangle getGlyphAtlasRec(int codepoint) {
                return GetGlyphAtlasRec(*_font, codepoint);
            };

            std::string loadUTF8(const int *codepoints, int length) {
                return LoadUTF8(codepoints, length);
            };

            void unloadUTF8(std::string &text) {
                return UnloadUTF8((char *) text.c_str());
            };

            int *loadCodepoints(const std::string &text, int *count) {
                return LoadCodepoints(text.c_str(), count);
            };

            void unloadCodepoints(int *codepoints) {
                return UnloadCodepoints(codepoints);
            };

            int getCodepointCount(const std::string &text) {
                return GetCodepointCount(text.c_str());
            };

            int getCodepoint(const std::string &text, int *codepointSize) {
                return GetCodepoint(text.c_str(), codepointSize);
            };

            int getCodepointNext(const std::string &text, int *codepointSize) {
                return GetCodepointNext(text.c_str(), codepointSize);
            };

            int getCodepointPrevious(const std::string &text, int *codepointSize) {
                return GetCodepointPrevious(text.c_str(), codepointSize);
            };

            std::string rCodepointToUTF8(int codepoint, int *utf8Size) {
                return CodepointToUTF8(codepoint, utf8Size);
            };

            std::unique_ptr<Font> _font;

    };

} // ZappyGui

#endif //ZAPPY_GUI_FONT_HPP
