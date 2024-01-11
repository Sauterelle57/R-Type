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
#include "renderer/IRenderTexture.hpp"

namespace ECS {
    class ModalSystem : public System {
        public:
            void update(std::shared_ptr<RL::IWindow> &window, std::shared_ptr<RL::IRenderTexture> &target);
    };
}

#endif //RTYPE_MODAL_HPP
