/*
** EPITECH PROJECT, 2023
** zappy_gui
** File description:
** ICamera2D.hpp
*/

#ifndef ZAPPY_GUI_ICAMERA2D_HPP
#define ZAPPY_GUI_ICAMERA2D_HPP

struct Matrix;

namespace ZappyGui {

    class ICamera2D {
        public:
            virtual ~ICamera2D() = default;
            virtual Matrix getMatrix2D() const = 0;
            virtual void beginMode() = 0;
            virtual void endMode() = 0;
    };

} // ZappyGui

#endif //ZAPPY_GUI_ICAMERA2D_HPP
