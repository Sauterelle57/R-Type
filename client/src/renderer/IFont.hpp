/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IFont.hpp
*/

#ifndef raylib_IFONT_HPP
#define raylib_IFONT_HPP

#include <iostream>
struct Image;
struct GlyphInfo;
struct Rectangle;
struct Color;
struct Vector2;

namespace RL {

    class IFont {
        public:
            virtual ~IFont() = default;
            virtual void load(const std::string &fileName) = 0;
            virtual void loadEx(const std::string &fileName, int fontSize, int *fontChars, int glyphCount) = 0;
            virtual void loadFromImage(Image image, Color key, int firstChar) = 0;
            virtual bool isReady() = 0;
            virtual GlyphInfo *loadData(unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int glyphCount, int type) = 0;
            virtual Image genImageAtlas(const GlyphInfo *chars, Rectangle **recs, int glyphCount, int fontSize, int padding, int packMethod) = 0;
            virtual void unloadData(GlyphInfo *chars, int glyphCount) = 0;
            virtual bool exportAsCode(const std::string &fileName) = 0;
            virtual Vector2 measureTextEx(const std::string &text, float fontSize, float spacing) = 0;
            virtual int getGlyphIndex(int codepoint) = 0;
            virtual GlyphInfo getGlyphInfo(int codepoint) = 0;
            virtual Rectangle getGlyphAtlasRec(int codepoint) = 0;
            virtual std::string loadUTF8(const int *codepoints, int length) = 0;
            virtual void unloadUTF8(std::string &text) = 0;
            virtual int *loadCodepoints(const std::string &text, int *count) = 0;
            virtual void unloadCodepoints(int *codepoints) = 0;
            virtual int getCodepointCount(const std::string &text) = 0;
            virtual int getCodepoint(const std::string &text, int *codepointSize) = 0;
            virtual int getCodepointNext(const std::string &text, int *codepointSize) = 0;
            virtual int getCodepointPrevious(const std::string &text, int *codepointSize) = 0;
            virtual std::string rCodepointToUTF8(int codepoint, int *utf8Size) = 0;
    };

} // RL

#endif //raylib_IFONT_HPP
