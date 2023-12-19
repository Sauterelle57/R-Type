/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** IModel.hpp
*/

#ifndef raylib_IMODEL_HPP
#define raylib_IMODEL_HPP

struct BoundingBox;
struct Vector3;
struct Color;
struct ModelAnimation;

namespace RL {

    class IModel {
        public:
            virtual ~IModel() = default;
            virtual bool isReady() = 0;
            virtual BoundingBox getBoundingBox() = 0;
            virtual void draw(Vector3 position, float scale, Color tint) = 0;
            virtual void drawEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) = 0;
            virtual void drawWires(Vector3 position, float scale, Color tint) = 0;
            virtual void drawWiresEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) = 0;
            virtual void setMeshMaterial(int meshId, int materialId) = 0;
            virtual void updateAnimation(ModelAnimation anim, int frame) = 0;
            virtual bool isAnimationValid(ModelAnimation anim) = 0;
            virtual std::shared_ptr<Model> getModel() = 0;
            };

} // RL

#endif //raylib_IMODEL_HPP
