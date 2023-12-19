/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Material.hpp
*/

#ifndef raylib_MATERIAL_HPP
#define raylib_MATERIAL_HPP

#include <raylib.h>
#include <iostream>
#include <memory>
#include "IMaterial.hpp"

namespace RL {

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

} // RL

#endif //raylib_MATERIAL_HPP
