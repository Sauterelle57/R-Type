//
// Created by noahg on 11/01/2024.
//

#ifndef RTYPE_MODAL_HPP
#define RTYPE_MODAL_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include "renderer/IWindow.hpp"
#include "renderer/Utils.hpp"
#include "renderer/Shader.hpp"

namespace ECS {
    class ModalSystem : public System {
        public:

            void update(std::shared_ptr<RL::IWindow> &window, std::unique_ptr<RL::IShader> &blurShader, RenderTexture2D &target) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &modal = coordinatorPtr->getComponent<Modal>(entity);
                    modal.openClose(modal.active);
                    if (modal.active) {
                        blurShader->beginMode();
                        DrawTextureRec(target.texture, { 0, 0, static_cast<float>(target.texture.width), static_cast<float>(-target.texture.height) }, { 0, 0 }, WHITE);
                        blurShader->endMode();
                        window->drawRectangle(window->getRenderWidth() / 2 - modal.width / 2, window->getRenderHeight() / 2 - modal.height / 2, modal.width, modal.height, modal.color);
                        int textLength = RL::Utils::measureText(modal.title, modal.titleWidth);
                        window->drawText(modal.title, window->getRenderWidth() / 2 - textLength / 2, window->getRenderHeight() / 2 - modal.height / 2 + modal.titleWidth, modal.titleWidth, WHITE);
                    } else {
                        DrawTextureRec(target.texture, { 0, 0, static_cast<float>(target.texture.width), static_cast<float>(-target.texture.height) }, { 0, 0 }, WHITE);
                    }
                }
            }
    };
}

#endif //RTYPE_MODAL_HPP
