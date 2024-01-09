/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** collisions.hpp
*/

#ifndef RTYPE_COLLISIONS_HPP
#define RTYPE_COLLISIONS_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Vec3.hpp"
#include <vector>
#include "raymath.h"

namespace tls {

    struct BoundingBox {
        Vec3 min;
        Vec3 max;

        void applyMatrix(const Matrix& mat) {
            Vector3 corners[8] = {
                    {static_cast<float>(min._x), static_cast<float>(min._y), static_cast<float>(min._z)},
                    {static_cast<float>(max._x), static_cast<float>(min._y), static_cast<float>(min._z)},
                    {static_cast<float>(min._x), static_cast<float>(max._y), static_cast<float>(min._z)},
                    {static_cast<float>(max._x), static_cast<float>(max._y), static_cast<float>(min._z)},
                    {static_cast<float>(min._x), static_cast<float>(min._y), static_cast<float>(max._z)},
                    {static_cast<float>(max._x), static_cast<float>(min._y), static_cast<float>(max._z)},
                    {static_cast<float>(min._x), static_cast<float>(max._y), static_cast<float>(max._z)},
                    {static_cast<float>(max._x), static_cast<float>(max._y), static_cast<float>(max._z)}
            };

            for (int i = 0; i < 8; i++) {
                corners[i] = Vector3Transform(corners[i], mat);
            }

            Vector3 newMin = corners[0];
            Vector3 newMax = corners[0];
            for (int i = 1; i < 8; i++) {
                newMin = Vector3Min(newMin, corners[i]);
                newMax = Vector3Max(newMax, corners[i]);
            }

            min = {newMin.x, newMin.y, newMin.z};
            max = {newMax.x, newMax.y, newMax.z};
        }

        BoundingBox transform(const Vec3& position, const Vec3& scale) const {
            BoundingBox transformed;
            transformed.min = {min._x * scale._x + position._x, min._y * scale._y + position._y, min._z * scale._z + position._z};
            transformed.max = {max._x * scale._x + position._x, max._y * scale._y + position._y, max._z * scale._z + position._z};
            return transformed;
        }

        bool intersects(const BoundingBox& other) const {
            return (min._x <= other.max._x && max._x >= other.min._x) &&
                   (min._y <= other.max._y && max._y >= other.min._y) &&
                   (min._z <= other.max._z && max._z >= other.min._z);
        }
    };

    BoundingBox loadModelAndGetBoundingBox(const std::string& path);
    BoundingBox calculateBoundingBoxForAllMeshes(const aiScene *scene);
}

#endif //RTYPE_COLLISIONS_HPP
