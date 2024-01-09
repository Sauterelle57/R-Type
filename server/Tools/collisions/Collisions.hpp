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

namespace tls {

    struct BoundingBox {
        Vec3 min;
        Vec3 max;

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
