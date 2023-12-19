//
// Created by noah on 12/16/23.
//

#ifndef RTYPE_COMPONENTS_HPP
#define RTYPE_COMPONENTS_HPP

#include <cstdint>

namespace ECS {
    using ComponentType = std::uint8_t;

    constexpr ComponentType MAX_COMPONENTS = 128;
}

#endif //RTYPE_COMPONENTS_HPP
