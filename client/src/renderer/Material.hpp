/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Material.hpp
*/

#ifndef ZAPPY_GUI_MATERIAL_HPP
#define ZAPPY_GUI_MATERIAL_HPP

#include <raylib.h>
#include <iostream>
#include <memory>
#include "IMaterial.hpp"

namespace ZappyGui {

    class ZMaterial : public IMaterial {
        public:
            ZMaterial(const std::string &fileName, int *materialCount) {
                _material = std::make_unique<Material>(*LoadMaterials(fileName.c_str(), materialCount));
            };

            ZMaterial() {
                _material = std::make_unique<Material>(LoadMaterialDefault());
            };

            ~ZMaterial() {
                UnloadMaterial(*_material);
            };

            bool isReady() {
                return IsMaterialReady(*_material);
            };

            void setTexture(int mapType, Texture2D texture) {
                return SetMaterialTexture(_material.get(), mapType, texture);
            };

            static void setTextureFromModel(Material *mat, int mapType, Texture2D texture) {
                return SetMaterialTexture(mat, mapType, texture);
            };

            std::unique_ptr<Material> &getMaterial() {
                return _material;
            };

            std::unique_ptr<Material> _material;
    };

} // ZappyGui

#endif //ZAPPY_GUI_MATERIAL_HPP
