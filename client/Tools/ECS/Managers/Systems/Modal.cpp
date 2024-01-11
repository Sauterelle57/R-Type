//
// Created by noahg on 11/01/2024.
//

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "Modal.hpp"

void ECS::ModalSystem::update(std::shared_ptr<RL::IWindow> &window, std::shared_ptr<RL::IRenderTexture> &target) {
    auto coordinatorPtr = _coordinator.lock();
    if (!coordinatorPtr) {
        return;
    }

    static std::unique_ptr<RL::IShader> blurShader = std::make_unique<RL::ZShader>("./client/resources/shaders/blur.fs");

    for (auto const &entity : _entities) {
        auto &modal = coordinatorPtr->getComponent<Modal>(entity);

        modal.openClose(modal.active);
        if (modal.active) {
            blurShader->beginMode();
            target->draw(0, 0, WHITE);
            blurShader->endMode();
            window->drawRectangle(0, 0, window->getRenderWidth(), window->getRenderHeight(), {0, 0, 0, 100});
            window->drawRectangle(window->getRenderWidth() / 2 - modal.width / 2, window->getRenderHeight() / 2 - modal.height / 2, modal.width, modal.height, modal.color);
            int textLength = RL::Utils::measureText(modal.title, modal.titleWidth);
            window->drawText(modal.title, window->getRenderWidth() / 2 - textLength / 2, window->getRenderHeight() / 2 - modal.height / 2 + modal.titleWidth, modal.titleWidth, WHITE);

            for (auto &slideBar: modal.slideBars) {
                float lastValue = slideBar.value;
                GuiSliderBar(slideBar.bounds, slideBar.textLeft.c_str(), slideBar.textRight.c_str(), &slideBar.value, slideBar.minValue, slideBar.maxValue);
                if (lastValue != slideBar.value) {
                    slideBar.onChange(slideBar.value);
                }
            }

            for (auto& button: modal.buttons) {
                if (GuiButton(button.bounds, button.text.c_str())) {
                    button.onClick();
                }
            }

            for (auto &checkBox: modal.checkBoxes) {
                bool lastValue = checkBox.value;
                GuiCheckBox(checkBox.bounds, checkBox.text.c_str(), &checkBox.value);
                if (checkBox.value != lastValue) {
                    checkBox.onChange(checkBox.value);
                }
            }
        }
    }
}