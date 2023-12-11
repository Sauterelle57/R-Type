/*
** EPITECH PROJECT, 2023
** bsraytracer
** File description:
** tlsUtils.hpp
*/

#ifndef RTYPE_UTILS_HPP
#define RTYPE_UTILS_HPP

#include "../Vec3/Vec3.hpp"
#include <algorithm>
#include <cmath>

namespace tls {

    class Utils {
        public:
            static bool equal(double a, double b);
            static bool inf(double a, double b);
            static bool sup(double a, double b);
            static double distance(const tls::Vec3 &aColor, const tls::Vec3 &bColor);

    };

} // tls

#endif //RTYPE_UTILS_HPP
