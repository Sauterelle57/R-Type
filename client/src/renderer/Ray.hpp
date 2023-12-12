/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Ray.hpp
*/

#ifndef ZAPPY_GUI_RAY_HPP
#define ZAPPY_GUI_RAY_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IRay.hpp"

namespace ZappyGui {

    class ZRay : public IRay {
        public:
            ZRay(Vector3 position, Vector3 direction) {
                _ray = std::make_unique<Ray>(Ray{position, direction});
            };
            ZRay(Ray ray) {
                _ray = std::make_unique<Ray>(ray);
            };
            ~ZRay() = default;

            RayCollision getCollisionSphere(Vector3 center, float radius) {
                return GetRayCollisionSphere(*_ray, center, radius);
            };

            RayCollision getCollisionBox(BoundingBox box) {
                return GetRayCollisionBox(*_ray, box);
            };

            RayCollision getCollisionMesh(Mesh mesh, Matrix transform) {
                return GetRayCollisionMesh(*_ray, mesh, transform);
            };

            RayCollision getCollisionTriangle(Vector3 p1, Vector3 p2, Vector3 p3) {
                return GetRayCollisionTriangle(*_ray, p1, p2, p3);
            };

            RayCollision getCollisionQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) {
                return GetRayCollisionQuad(*_ray, p1, p2, p3, p4);
            };

            void draw(Color color) {
                return DrawRay(*_ray, color);
            };

            std::unique_ptr<Ray> _ray;
    };

} // ZappyGui

#endif //ZAPPY_GUI_RAY_HPP
