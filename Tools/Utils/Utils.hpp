/*
** EPITECH PROJECT, 2023
** bsraytracer
** File description:
** tlsUtils.hpp
*/

#ifndef RTYPE_UTILS_HPP
#define RTYPE_UTILS_HPP

#include <algorithm>
#include <cmath>

namespace tls {

    class Utils {
        public:
            static bool equal(double a, double b);
            static bool inf(double a, double b);
            static bool sup(double a, double b);
            static int getRandomValue(int a, int b);
    };

} // tls

#endif //RTYPE_UTILS_HPP
