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
#include "../../../Utils/Utils.hpp"
#include "../../../Vec4/Vec4.hpp"
#include "../../../Vec3/Vec3.hpp"
#include "../../../../client/src/renderer/IModel.hpp"

namespace ECS {
    struct Transform {
        tls::Vec3 position;
        tls::Vec4 rotation;
        tls::Vec3 scale;
    };

    struct Model {
        std::shared_ptr<RL::IModel> model;
    };

    using ComponentType = std::uint8_t;

    constexpr ComponentType MAX_COMPONENTS = 128;
}

#endif //RTYPE_COMPONENT_HPP
