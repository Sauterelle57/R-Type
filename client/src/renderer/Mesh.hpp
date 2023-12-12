/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Mesh.hpp
*/

#ifndef ZAPPY_GUI_MESH_HPP
#define ZAPPY_GUI_MESH_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IMesh.hpp"

namespace ZappyGui {

    class ZMesh : public IMesh {
        public:
            ZMesh() = default;

            ~ZMesh() {
                if (_canUnload) {
                    UnloadMesh(*_mesh);
                }
            };

            void upload(bool dynamic) {
                return UploadMesh(_mesh.get(), dynamic);
            };

            void updateBuffer(int index, const void *data, int dataSize, int offset) {
                return UpdateMeshBuffer(*_mesh, index, data, dataSize, offset);
            };

            void draw(Material material, Matrix transform) {
                return DrawMesh(*_mesh, material, transform);
            };

            void drawInstanced(Material material, const Matrix *transforms, int instances) {
                return DrawMeshInstanced(*_mesh, material, transforms, instances);
            };

            static void drawInstanced(Mesh mesh, Material material, const Matrix *transforms, int instances) {
                return DrawMeshInstanced(mesh, material, transforms, instances);
            };

            bool exportMesh(const std::string &fileName) {
                return ExportMesh(*_mesh, fileName.c_str());
            };

            BoundingBox getBoundingBox() {
                return GetMeshBoundingBox(*_mesh);
            };

            void genTangents() {
                return GenMeshTangents(_mesh.get());
            };

            void genPoly(int sides, float radius) {
                _mesh = std::make_unique<Mesh>(GenMeshPoly(sides, radius));
            };

            void genPlane(float width, float length, int resX, int resZ) {
                _mesh = std::make_unique<Mesh>(GenMeshPlane(width, length, resX, resZ));
            };

            void genCube(float width, float height, float length) {
                _mesh = std::make_unique<Mesh>(GenMeshCube(width, height, length));
            };

            static Mesh genMeshCube(float width, float height, float length) {
                return GenMeshCube(width, height, length);
            };

            void genSphere(float radius, int rings, int slices) {
                _mesh = std::make_unique<Mesh>(GenMeshSphere(radius, rings, slices));
            };

            void genHemiSphere(float radius, int rings, int slices) {
                _mesh = std::make_unique<Mesh>(GenMeshHemiSphere(radius, rings, slices));
            };

            void genCylinder(float radius, float height, int slices) {
                _mesh = std::make_unique<Mesh>(GenMeshCylinder(radius, height, slices));
            };

            void genCone(float radius, float height, int slices) {
                _mesh = std::make_unique<Mesh>(GenMeshCone(radius, height, slices));
            };

            void genTorus(float radius, float size, int radSeg, int sides) {
                _mesh = std::make_unique<Mesh>(GenMeshTorus(radius, size, radSeg, sides));
            };

            void genKnot(float radius, float size, int radSeg, int sides) {
                _mesh = std::make_unique<Mesh>(GenMeshKnot(radius, size, radSeg, sides));
            };

            void genHeightmap(Image heightmap, Vector3 size) {
                _mesh = std::make_unique<Mesh>(GenMeshHeightmap(heightmap, size));
            };

            void genCubicmap(Image cubicmap, Vector3 cubeSize) {
                _mesh = std::make_unique<Mesh>(GenMeshCubicmap(cubicmap, cubeSize));
            };

            void upload(Mesh mesh) {
                _mesh = std::make_unique<Mesh>(mesh);
            };

            Mesh getMesh() const {
                return *_mesh;
            }

            void setCanUnload(bool canUnload) {
                _canUnload = canUnload;
            }

            std::unique_ptr<Mesh> _mesh;
            bool _canUnload = true;
    };

} // ZappyGui

#endif //ZAPPY_GUI_MESH_HPP
