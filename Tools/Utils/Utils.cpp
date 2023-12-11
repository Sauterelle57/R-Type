/*
** EPITECH PROJECT, 2023
** bsraytracer
** File description:
** tlsUtils.cpp
*/

#include "Utils.hpp"

namespace tls {
    bool Utils::equal(double a, double b) {
        return (a - b) < 0.0000000001 && (a - b) > -0.0000000001;
    }

    bool Utils::inf(double a, double b) {
        return (a - b) < 0.0000000001;
    }

    bool Utils::sup(double a, double b) {
        return (a - b) > 0.0000000001;
    }

    double Utils::distance(const tls::Vec3& aColor, const tls::Vec3& bColor) {
        return sqrt(pow(aColor._x - bColor._x, 2) + pow(aColor._y - bColor._y, 2) + pow(aColor._z - bColor._z, 2));
    }

} // tls