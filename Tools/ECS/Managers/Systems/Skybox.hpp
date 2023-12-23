/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** Skybox.hpp
*/

#ifndef RTYPE_SKYBOX_HPP
#define RTYPE_SKYBOX_HPP

#include <iostream>
#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include "renderer/renderer.hpp"
#include "renderer/Utils.hpp"
#include "renderer/Mesh.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Image.hpp"

namespace ECS {
    class SkyBoxSystem : public System {
        public:
            void init(Entity entity, bool isHdr, const std::string &path) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                auto &element = coordinatorPtr->getComponent<SkyBox>(entity);


                Mesh cube = RL::ZMesh::genMeshCube(1.0f, 1.0f, 1.0f);
                element.skybox = std::make_shared<RL::ZModel>(cube);

                element.skybox->getModel()->materials[0].shader = RL::ZShader::load("./client/resources/shaders/skybox.vs", "./client/resources/shaders/skybox.fs");

                int mpc[1] = { MATERIAL_MAP_CUBEMAP };
                int hdr[1] = { isHdr ? 1 : 0 };
                int zero[1] = { 0 };
                RL::ZShader::setValue(element.skybox->getModel()->materials[0].shader, RL::ZShader::getLocation(element.skybox->getModel()->materials[0].shader, "environmentMap"), mpc, SHADER_UNIFORM_INT);
                RL::ZShader::setValue(element.skybox->getModel()->materials[0].shader, RL::ZShader::getLocation(element.skybox->getModel()->materials[0].shader, "doGamma"), hdr, SHADER_UNIFORM_INT);
                RL::ZShader::setValue(element.skybox->getModel()->materials[0].shader, RL::ZShader::getLocation(element.skybox->getModel()->materials[0].shader, "vflipped"), hdr, SHADER_UNIFORM_INT);

                std::shared_ptr<RL::ZShader> shdrCubemap = std::make_shared<RL::ZShader>("./client/resources/shaders/cubemap.vs", "./client/resources/shaders/cubemap.fs");

                shdrCubemap->setValue(shdrCubemap->getLocation("equirectangularMap"), zero, SHADER_UNIFORM_INT);

                if (isHdr) {
                    Texture2D panorama;
                    panorama = RL::ZTexture::load(path);
                    element.skybox->getModel()->materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = RL::ZTexture::genCubemap(*shdrCubemap->getShader(), panorama, 4096, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
                } else {
                    RL::ZImage img(path);
                    element.skybox->getModel()->materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = RL::ZTexture::loadCubemap(*img.getImage(), CUBEMAP_LAYOUT_AUTO_DETECT);
                }
            };

            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &skybox = coordinatorPtr->getComponent<SkyBox>(entity);
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                    RL::Utils::disableBackfaceCulling();
                    RL::Utils::disableDepthMask();
                    skybox.skybox->draw(transform.position, transform.scale, WHITE);
                    RL::Utils::enableBackfaceCulling();
                    RL::Utils::enableDepthMask();
                }
            }

    };

} // RT

#endif //RTYPE_SKYBOX_HPP
