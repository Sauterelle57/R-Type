/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IRay.hpp
*/

#ifndef raylib_IRAY_HPP
#define raylib_IRAY_HPP

struct RayCollision;
struct Vector3;
struct BoundingBox;
struct Mesh;
struct Matrix;
struct Color;

namespace RL {

    class IRay {
        public:
            virtual ~IRay() = default;
            virtual RayCollision getCollisionSphere(Vector3 center, float radius) = 0;
            virtual RayCollision getCollisionBox(BoundingBox box) = 0;
            virtual RayCollision getCollisionMesh(Mesh mesh, Matrix transform) = 0;
            virtual RayCollision getCollisionTriangle(Vector3 p1, Vector3 p2, Vector3 p3) = 0;
            virtual RayCollision getCollisionQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) = 0;
            virtual void draw(Color color) = 0;
    };

} // RL

#endif //raylib_IRAY_HPP
