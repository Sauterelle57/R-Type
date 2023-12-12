/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** ITexture.hpp
*/

#ifndef ZAPPY_GUI_ITEXTURE_HPP
#define ZAPPY_GUI_ITEXTURE_HPP

struct Rectangle;
struct Color;
struct Vector2;
struct NPatchInfo;

namespace ZappyGui {

    class ITexture {
        public:
            virtual ~ITexture() = default;
            virtual void setShapes(Rectangle source) = 0;
            virtual bool isReady() = 0;
            virtual void update(const void *pixels) = 0;
            virtual void updateRec(Rectangle rec, const void *pixels) = 0;
            virtual void genMipmaps() = 0;
            virtual void setFilter(int filter) = 0;
            virtual void setWrap(int wrap) = 0;
            virtual void draw(int posX, int posY, Color tint) = 0;
            virtual void drawV(Vector2 position, Color tint) = 0;
            virtual void drawEx(Vector2 position, float rotation, float scale, Color tint) = 0;
            virtual void drawRec(Rectangle source, Vector2 position, Color tint) = 0;
            virtual void drawPro(Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) = 0;
            virtual void drawNPatch(NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint) = 0;
            virtual std::shared_ptr<Texture> getTexture() = 0;
        };

} // ZappyGui

#endif //ZAPPY_GUI_ITEXTURE_HPP
