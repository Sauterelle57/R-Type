//
// Created by noah on 12/19/23.
//

#ifndef RTYPE_IVEC3_HPP
#define RTYPE_IVEC3_HPP

#include <raylib.h>

namespace tls {
    struct Vec3;
    class IVec3 {
        public:
            virtual ~IVec3() = default;

            virtual Vec3 &operator=(const Vec3 &vector) = 0;
            virtual Vec3 &operator=(Vec3 &&vector) = 0;
            virtual Vec3 operator+(const Vec3 &vector) const = 0;
            virtual Vec3 &operator+=(const Vec3 &vector) = 0;
            virtual Vec3 operator-(const Vec3 &vector) const = 0;
            virtual Vec3 &operator-=(const Vec3 &vector) = 0;
            virtual Vec3 operator*(const Vec3 &vector) const = 0;
            virtual Vec3 &operator*=(const Vec3 &vector) = 0;
            virtual Vec3 operator/(const Vec3 &vector) const = 0;
            virtual Vec3 &operator/=(const Vec3 &vector) = 0;
            virtual Vec3 operator*(double value) const = 0;
            virtual Vec3 operator+(double value) const = 0;
            virtual Vec3 &operator*=(double value) = 0;
            virtual Vec3 &operator+=(double value) = 0;
            virtual Vec3 operator/(double value) const = 0;
            virtual Vec3 &operator/=(double value) = 0;
            virtual bool operator==(const Vec3 &vector) const = 0;
            virtual bool operator!=(const Vec3 &vector) const = 0;
            virtual operator Vector3() const = 0;
            virtual Vec3 normalized() const = 0;
            virtual double dot(const Vec3 &vector) const = 0;
            virtual Vec3 cross(const Vec3 &other) const = 0;
            virtual double length() const = 0;
    };
}

#endif //RTYPE_IVEC3_HPP
