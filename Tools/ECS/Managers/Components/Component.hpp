/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ComponentsManager
*/

#ifndef RTYPE_COMPONENT_HPP
#define RTYPE_COMPONENT_HPP

#include <cstdint>
#include <memory>
#include "Utils.hpp"
#include "Vec4.hpp"
#include "Vec3.hpp"
#include "renderer/IModel.hpp"
#include "renderer/ITexture.hpp"

namespace ECS {
    struct Transform {
        tls::Vec3 position;
        tls::Vec4 rotation;
        float scale;
    };

    struct Model {
        std::shared_ptr<RL::IModel> model;
        std::shared_ptr<RL::ITexture> texture;
    };

    struct Player {
        int key_up;
        int key_down;
        int key_left;
        int key_right;
        int key_shoot;
        int key_validate;
        int key_cancel;
        int key_settings;
    };

    using ComponentType = std::uint8_t;

    constexpr ComponentType MAX_COMPONENTS = 128;
}

#endif //RTYPE_COMPONENT_HPP
