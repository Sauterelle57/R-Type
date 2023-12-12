/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Model.hpp
*/

#ifndef ZAPPY_GUI_MODEL_HPP
#define ZAPPY_GUI_MODEL_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "IModel.hpp"

namespace ZappyGui {

    class ZModel : public IModel {
        public:
            ZModel(const std::string &fileName) {
                _model = std::make_shared<Model>(LoadModel(fileName.c_str()));
            };

            ZModel(Mesh mesh) {
                _model = std::make_shared<Model>(LoadModelFromMesh(mesh));
            };

            ~ZModel() {
                UnloadModel(*_model);
            }

            bool isReady() {
                return IsModelReady(*_model);
            };

            BoundingBox getBoundingBox() {
                return GetModelBoundingBox(*_model);
            };

            void draw(Vector3 position, float scale, Color tint) {
                return DrawModel(*_model, position, scale, tint);
            };

            void drawEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
                return DrawModelEx(*_model, position, rotationAxis, rotationAngle, scale, tint);
            };

            void drawWires(Vector3 position, float scale, Color tint) {
                return DrawModelWires(*_model, position, scale, tint);
            };

            void drawWiresEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
                return DrawModelWiresEx(*_model, position, rotationAxis, rotationAngle, scale, tint);
            };

            void setMeshMaterial(int meshId, int materialId) {
                return SetModelMeshMaterial(_model.get(), meshId, materialId);
            };

            void updateAnimation(ModelAnimation anim, int frame) {
                return UpdateModelAnimation(*_model, anim, frame);
            };

            bool isAnimationValid(ModelAnimation anim) {
                return IsModelAnimationValid(*_model, anim);
            };

            std::shared_ptr<Model> getModel() {
                return _model;
            }

            std::shared_ptr<Model> _model;

    };

} // ZappyGui

#endif //ZAPPY_GUI_MODEL_HPP
