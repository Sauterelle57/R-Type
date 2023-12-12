//
// Created by noah on 12/12/23.
//

#ifndef RTYPE_MOVE_HPP
#define RTYPE_MOVE_HPP

#include "System.hpp"

namespace ECS {
    class Move : public System {
        public:
            void update(Coordinator &coo) {
                for (auto const &entity : _entities) {
                    auto &transform = coo.getComponent<Transform>(entity);
                    transform.position.y -= 0.1;
                    if (transform.position.y < 0)
                        transform.position.y = 20;
                }
            }
    };
}

#endif //RTYPE_MOVE_HPP
