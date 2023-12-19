/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IMesh.hpp
*/

#ifndef raylib_IMESH_HPP
#define raylib_IMESH_HPP

#include <iostream>
#include "raylib.h"

struct Material;
struct Matrix;
struct BoundingBox;
struct Image;
struct Vector3;

namespace RL {

    class IMesh {
        public:
            virtual ~IMesh() = default;
            virtual void upload(bool dynamic) = 0;
            virtual void upload(Mesh mesh) = 0;
            virtual void updateBuffer(int index, const void *data, int dataSize, int offset) = 0;
            virtual void draw(Material material, Matrix transform) = 0;
            virtual void drawInstanced(Material material, const Matrix *transforms, int instances) = 0;
            virtual bool exportMesh(const std::string &fileName) = 0;
            virtual BoundingBox getBoundingBox() = 0;
            virtual void genTangents() = 0;
            virtual void genPoly(int sides, float radius) = 0;
            virtual void genPlane(float width, float length, int resX, int resZ) = 0;
            virtual void genCube(float width, float height, float length) = 0;
            virtual void genSphere(float radius, int rings, int slices) = 0;
            virtual void genHemiSphere(float radius, int rings, int slices) = 0;
            virtual void genCylinder(float radius, float height, int slices) = 0;
            virtual void genCone(float radius, float height, int slices) = 0;
            virtual void genTorus(float radius, float size, int radSeg, int sides) = 0;
            virtual void genKnot(float radius, float size, int radSeg, int sides) = 0;
            virtual void genHeightmap(Image heightmap, Vector3 size) = 0;
            virtual void genCubicmap(Image cubicmap, Vector3 cubeSize) = 0;
            virtual Mesh getMesh() const = 0;
            virtual void setCanUnload(bool canUnload) = 0;
            };

} // RL

#endif //raylib_IMESH_HPP
