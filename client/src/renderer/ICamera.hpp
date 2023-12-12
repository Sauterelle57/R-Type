/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** ICamera.hpp
*/

#ifndef raylib_ICAMERA_HPP
#define raylib_ICAMERA_HPP

#include <iostream>
#include <memory>

struct Ray;
struct Matrix;
struct Vector2;
struct Vector3;
struct Texture;
struct Color;
struct Rectangle;

namespace RL {

    class ICamera {
        public:
            virtual ~ICamera() = default;
            virtual Ray getMouseRay(Vector2 mousePosition) = 0;
            virtual Matrix getMatrix() = 0;
            virtual void update(int mode) = 0;
            virtual void updatePro(Vector3 movement, Vector3 rotation, float zoom) = 0;
            virtual void beginMode() = 0;
            virtual void endMode() = 0;
            virtual void drawBillboard(Texture2D texture, Vector3 position, float size, Color tint) = 0;
            virtual void drawBillboardRec(Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint) = 0;
            virtual void drawBillboardPro(Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint) = 0;
            virtual Vector3 getPosition() = 0;
            virtual void setPosition(Vector3 position) = 0;
            virtual Vector3 getTarget() = 0;
            virtual void setTarget(Vector3 target) = 0;
            virtual Vector3 getUp() = 0;
            virtual void setUp(Vector3 up) = 0;
            virtual float getFovy() = 0;
            virtual void setFovy(float fovy) = 0;
            virtual int getProjection() = 0;
            virtual void setProjection(int projection) = 0;
    };

} // RL

#endif //raylib_ICAMERA_HPP
