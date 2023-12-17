/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Vec3
*/

#ifndef RTYPE_VEC3_HPP
#define RTYPE_VEC3_HPP

#include "raylib.h"

namespace tls {
    class Vec3 {
        public:
            // Constructors
            Vec3();
            Vec3(double x, double y, double z);
            Vec3(const Vec3 &vector);
            Vec3(Vec3 &&vector) = default;
            Vec3(const Vec3 &point1, const Vec3 &point2);

            // Destructor
            ~Vec3() = default;

            // Operators
            Vec3 &operator=(const Vec3 &vector) = default;
            Vec3 &operator=(Vec3 &&vector) = default;

            Vec3 operator+(const Vec3 &vector) const;
            Vec3 &operator+=(const Vec3 &vector);
            Vec3 operator-(const Vec3 &vector) const;
            Vec3 &operator-=(const Vec3 &vector);
            Vec3 operator*(const Vec3 &vector) const;
            Vec3 &operator*=(const Vec3 &vector);
            Vec3 operator/(const Vec3 &vector) const;
            Vec3 &operator/=(const Vec3 &vector);

            Vec3 operator*(double value) const;
            Vec3 operator+(double value) const;
            Vec3 &operator*=(double value);
            Vec3 &operator+=(double value);
            Vec3 operator/(double value) const;
            Vec3 &operator/=(double value);

            operator Vector3() const;

            bool operator==(const Vec3 &vector) const;
            bool operator!=(const Vec3 &vector) const;

            Vec3 normalized() const;

            // Methods
            double dot(const Vec3 &vector) const;
            Vec3 cross(const Vec3 &other) const;
            double length() const;

            // Variables
            double _x;
            double _y;
            double _z;
    };

} // tls

#endif //RTYPE_VEC3_HPP
