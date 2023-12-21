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
} // tls