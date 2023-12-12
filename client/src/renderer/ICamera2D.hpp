/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** ICamera2D.hpp
*/

#ifndef raylib_ICAMERA2D_HPP
#define raylib_ICAMERA2D_HPP

struct Matrix;

namespace RL {

    class ICamera2D {
        public:
            virtual ~ICamera2D() = default;
            virtual Matrix getMatrix2D() const = 0;
            virtual void beginMode() = 0;
            virtual void endMode() = 0;
    };

} // RL

#endif //raylib_ICAMERA2D_HPP
