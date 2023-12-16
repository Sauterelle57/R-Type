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
