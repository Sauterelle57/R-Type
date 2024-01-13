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

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef DEG2RAD
#define DEG2RAD (PI/180.0f)
#endif

namespace tls {

    typedef struct Matrix {
        float m0, m4, m8, m12;      // Matrix first row (4 components)
        float m1, m5, m9, m13;      // Matrix second row (4 components)
        float m2, m6, m10, m14;     // Matrix third row (4 components)
        float m3, m7, m11, m15;     // Matrix fourth row (4 components)
    } Matrix;

    inline Vec3 Vector3Transform(Vec3 v, Matrix mat) {
        Vec3 result = { 0, 0, 0 };

        float x = v._x;
        float y = v._y;
        float z = v._z;

        result._x = mat.m0*x + mat.m4*y + mat.m8*z + mat.m12;
        result._y = mat.m1*x + mat.m5*y + mat.m9*z + mat.m13;
        result._z = mat.m2*x + mat.m6*y + mat.m10*z + mat.m14;

        return result;
    }

    inline Vec3 Vector3Min(Vec3 v1, Vec3 v2) {
        Vec3 result = { 0, 0, 0 };

        result._x = fminf(v1._x, v2._x);
        result._y = fminf(v1._y, v2._y);
        result._z = fminf(v1._z, v2._z);

        return result;
    }

    inline Vec3 Vector3Max(Vec3 v1, Vec3 v2) {
        Vec3 result = { 0, 0, 0 };

        result._x = fmaxf(v1._x, v2._x);
        result._y = fmaxf(v1._y, v2._y);
        result._z = fmaxf(v1._z, v2._z);

        return result;
    }

    inline Matrix MatrixScale(float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f) {
        Matrix result = { scaleX, 0.0f, 0.0f, 0.0f,
                          0.0f, scaleY, 0.0f, 0.0f,
                          0.0f, 0.0f, scaleZ, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f };

        return result;
    }

    inline Matrix MatrixIdentity(void) {
        Matrix result = { 1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f }; // MatrixIdentity()

        return result;
    }

    inline Matrix MatrixRotateY(float angle) {
        Matrix result = { 1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f };

        float cosres = cosf(angle);
        float sinres = sinf(angle);

        result.m5 = cosres;
        result.m6 = sinres;
        result.m9 = -sinres;
        result.m10 = cosres;

        return result;
    }

    inline Matrix MatrixRotateX(float angle)
    {
        Matrix result = { 1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f }; // MatrixIdentity()

        float cosres = cosf(angle);
        float sinres = sinf(angle);

        result.m0 = cosres;
        result.m2 = -sinres;
        result.m8 = sinres;
        result.m10 = cosres;

        return result;
    }

    inline Matrix MatrixRotateZ(float angle)
    {
        Matrix result = { 1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f }; // MatrixIdentity()

        float cosres = cosf(angle);
        float sinres = sinf(angle);

        result.m0 = cosres;
        result.m1 = sinres;
        result.m4 = -sinres;
        result.m5 = cosres;

        return result;
    }

    inline Matrix MatrixMultiply(Matrix left, Matrix right) {
        Matrix result = { 0 };

        result.m0 = left.m0*right.m0 + left.m1*right.m4 + left.m2*right.m8 + left.m3*right.m12;
        result.m1 = left.m0*right.m1 + left.m1*right.m5 + left.m2*right.m9 + left.m3*right.m13;
        result.m2 = left.m0*right.m2 + left.m1*right.m6 + left.m2*right.m10 + left.m3*right.m14;
        result.m3 = left.m0*right.m3 + left.m1*right.m7 + left.m2*right.m11 + left.m3*right.m15;
        result.m4 = left.m4*right.m0 + left.m5*right.m4 + left.m6*right.m8 + left.m7*right.m12;
        result.m5 = left.m4*right.m1 + left.m5*right.m5 + left.m6*right.m9 + left.m7*right.m13;
        result.m6 = left.m4*right.m2 + left.m5*right.m6 + left.m6*right.m10 + left.m7*right.m14;
        result.m7 = left.m4*right.m3 + left.m5*right.m7 + left.m6*right.m11 + left.m7*right.m15;
        result.m8 = left.m8*right.m0 + left.m9*right.m4 + left.m10*right.m8 + left.m11*right.m12;
        result.m9 = left.m8*right.m1 + left.m9*right.m5 + left.m10*right.m9 + left.m11*right.m13;
        result.m10 = left.m8*right.m2 + left.m9*right.m6 + left.m10*right.m10 + left.m11*right.m14;
        result.m11 = left.m8*right.m3 + left.m9*right.m7 + left.m10*right.m11 + left.m11*right.m15;
        result.m12 = left.m12*right.m0 + left.m13*right.m4 + left.m14*right.m8 + left.m15*right.m12;
        result.m13 = left.m12*right.m1 + left.m13*right.m5 + left.m14*right.m9 + left.m15*right.m13;
        result.m14 = left.m12*right.m2 + left.m13*right.m6 + left.m14*right.m10 + left.m15*right.m14;
        result.m15 = left.m12*right.m3 + left.m13*right.m7 + left.m14*right.m11 + left.m15*right.m15;

        return result;
    }


    struct BoundingBox {
        Vec3 min;
        Vec3 max;

        void applyMatrix(const Matrix& mat) {
            Vec3 corners[8] = {
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

            Vec3 newMin = corners[0];
            Vec3 newMax = corners[0];
            for (int i = 1; i < 8; i++) {
                newMin = Vector3Min(newMin, corners[i]);
                newMax = Vector3Max(newMax, corners[i]);
            }

            min = {newMin._x, newMin._y, newMin._z};
            max = {newMax._x, newMax._y, newMax._z};
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
