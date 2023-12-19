/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** DrawModel
*/

#ifndef RTYPE_DRAWMODEL_HPP
#define RTYPE_DRAWMODEL_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include "renderer/Utils.hpp"

namespace ECS {
    class DrawModel : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                int count = 0;
                for (auto const &entity : _entities) {
                    count++;
                    auto &model = coordinatorPtr->getComponent<Model>(entity);
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                    transform.bounds = model.model->getBoundingBox();

                    Matrix matScale = MatrixScale(transform.scale, transform.scale, transform.scale);
                    Matrix matRotation = MatrixRotateXYZ({static_cast<float>(transform.rotation._x), static_cast<float>(transform.rotation._y), static_cast<float>(transform.rotation._z)});
                    Matrix matTranslation = MatrixTranslate(transform.position._x, transform.position._y, transform.position._z);

                    Vector3 scaledMin = Vector3Multiply(transform.bounds.min, {transform.scale, transform.scale, transform.scale});
                    Vector3 scaledMax = Vector3Multiply(transform.bounds.max, {transform.scale, transform.scale, transform.scale});

                    Vector3 points[8] = {
                        {scaledMin.x, scaledMin.y, scaledMin.z},
                        {scaledMin.x, scaledMin.y, scaledMax.z},
                        {scaledMin.x, scaledMax.y, scaledMin.z},
                        {scaledMin.x, scaledMax.y, scaledMax.z},
                        {scaledMax.x, scaledMin.y, scaledMin.z},
                        {scaledMax.x, scaledMin.y, scaledMax.z},
                        {scaledMax.x, scaledMax.y, scaledMin.z},
                        {scaledMax.x, scaledMax.y, scaledMax.z}
                    };

                    for (int i = 0; i < 8; i++) {
                        points[i] = Vector3Transform(points[i], matRotation);
                        points[i] = Vector3Transform(points[i], matTranslation);
                    }

                    Vector3 min = points[0];
                    Vector3 max = points[0];
                    for (int i = 1; i < 8; i++) {
                        min = Vector3Min(min, points[i]);
                        max = Vector3Max(max, points[i]);
                    }

                    transform.bounds = {min, max};

                    RL::Utils::drawBoundingBox(transform.bounds, RED);


                    if (model.texture)
                        model.model->getModel()->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(model.texture->getTexture());

                    model.model->drawEx(transform.position, {static_cast<float>(transform.rotation._x), static_cast<float>(transform.rotation._y), static_cast<float>(transform.rotation._z)}, transform.rotation._a,
                                        {transform.scale, transform.scale, transform.scale}, WHITE);
                }
                // std::cout << "DrawModel: " << count << std::endl;
            }
    };
}

#endif //RTYPE_DRAWMODEL_HPP
