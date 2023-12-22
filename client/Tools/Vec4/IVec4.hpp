/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IVec4
*/

#ifndef RTYPE_IVEC4_HPP
#define RTYPE_IVEC4_HPP

#include <raylib.h>

namespace tls {
    struct Vec4;
    class IVec4 {
        public:
            virtual ~IVec4() = default;

            virtual Vec4 &operator=(const Vec4 &vector) = 0;
            virtual Vec4 &operator=(Vec4 &&vector) = 0;
            virtual Vec4 operator+(const Vec4 &vector) const = 0;
            virtual Vec4 &operator+=(const Vec4 &vector) = 0;
            virtual Vec4 operator-(const Vec4 &vector) const = 0;
            virtual Vec4 &operator-=(const Vec4 &vector) = 0;
            virtual Vec4 operator*(const Vec4 &vector) const = 0;
            virtual Vec4 &operator*=(const Vec4 &vector) = 0;
            virtual Vec4 operator/(const Vec4 &vector) const = 0;
            virtual Vec4 &operator/=(const Vec4 &vector) = 0;
            virtual Vec4 operator*(double value) const = 0;
            virtual Vec4 operator+(double value) const = 0;
            virtual Vec4 &operator*=(double value) = 0;
            virtual Vec4 &operator+=(double value) = 0;
            virtual Vec4 operator/(double value) const = 0;
            virtual Vec4 &operator/=(double value) = 0;
            virtual bool operator==(const Vec4 &vector) const = 0;
            virtual operator Vector4() const = 0;
            virtual Vec4 normalized() const = 0;
            virtual double dot(const Vec4 &vector) const = 0;
            virtual double length() const = 0;
    };
}

#endif //RTYPE_IVEC4_HPP
