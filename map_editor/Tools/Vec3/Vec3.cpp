/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Vec3
*/

#include <complex>
#include "Vec3.hpp"
#include "Utils.hpp"
#include "Tools/Utils/Utils.hpp"

namespace tls {

    Vec3::Vec3() {
        _x = 0;
        _y = 0;
        _z = 0;
    }

    Vec3::Vec3(double x, double y, double z) {
        _x = x;
        _y = y;
        _z = z;
    }

    Vec3::Vec3(const Vec3 &vector) {
        _x = vector._x;
        _y = vector._y;
        _z = vector._z;
    }

    double Vec3::length() const {
        return std::sqrt(static_cast<double>(_x * _x) + static_cast<double>(_y * _y) + static_cast<double>(_z * _z));
    }

    Vec3 Vec3::operator+(const Vec3 &vector) const {
        Vec3 result;

        result._x = _x + vector._x;
        result._y = _y + vector._y;
        result._z = _z + vector._z;
        return result;
    }

    Vec3 &Vec3::operator+=(const Vec3 &vector) {
        _x += vector._x;
        _y += vector._y;
        _z += vector._z;
        return *this;
    }

    Vec3 Vec3::operator-(const Vec3 &vector) const {
        Vec3 result;

        result._x = _x - vector._x;
        result._y = _y - vector._y;
        result._z = _z - vector._z;
        return result;
    }

    Vec3 &Vec3::operator-=(const Vec3 &vector) {
        _x -= vector._x;
        _y -= vector._y;
        _z -= vector._z;
        return *this;
    }

    Vec3 Vec3::operator*(const Vec3 &vector) const {
        Vec3 result;

        result._x = _x * vector._x;
        result._y = _y * vector._y;
        result._z = _z * vector._z;
        return result;
    }

    Vec3 &Vec3::operator*=(const Vec3 &vector) {
        _x *= vector._x;
        _y *= vector._y;
        _z *= vector._z;
        return *this;
    }

    Vec3 Vec3::operator/(const Vec3 &vector) const {
        Vec3 result;

        result._x = _x / vector._x;
        result._y = _y / vector._y;
        result._z = _z / vector._z;
        return result;
    }

    Vec3 &Vec3::operator/=(const Vec3 &vector) {
        _x /= vector._x;
        _y /= vector._y;
        _z /= vector._z;
        return *this;
    }

    Vec3 Vec3::operator*(double value) const {
        Vec3 result;

        result._x = _x * value;
        result._y = _y * value;
        result._z = _z * value;
        return result;
    }

    Vec3 &Vec3::operator*=(double value) {
        _x *= value;
        _y *= value;
        _z *= value;
        return *this;
    }

    Vec3 Vec3::operator/(double value) const {
        Vec3 result;

        result._x = _x / value;
        result._y = _y / value;
        result._z = _z / value;
        return result;
    }

    Vec3 &Vec3::operator/=(double value) {
        _x /= value;
        _y /= value;
        _z /= value;
        return *this;
    }

    double Vec3::dot(const Vec3 &vector) const {
        return (_x * vector._x) + (_y * vector._y) + (_z * vector._z);
    }

    Vec3 Vec3::cross(const Vec3 &other) const {
        double x = _y * other._z - _z * other._y;
        double y = _z * other._x - _x * other._z;
        double z = _x * other._y - _y * other._x;
        return {x, y, z};
    }

    Vec3::Vec3(const Vec3 &point1, const Vec3 &point2) {
        _x = point2._x - point1._x;
        _y = point2._y - point1._y;
        _z = point2._z - point1._z;
    }

    Vec3 Vec3::operator+(double value) const {
        Vec3 result;

        result._x = _x + value;
        result._y = _y + value;
        result._z = _z + value;
        return result;
    }

    Vec3 &Vec3::operator+=(double value) {
        _x += value;
        _y += value;
        _z += value;
        return *this;
    }

    Vec3::operator Vector3() const {
        return Vector3{static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_z)};
    }

    Vec3 Vec3::normalized() const {
        double len = std::sqrt(dot(*this));

        tls::Vec3 normal(_x / len, _y / len, _z / len);
        return normal;
    }

    bool Vec3::operator==(const Vec3 &vector) const {
        return Utils::equal(_x, vector._x) && Utils::equal(_y, vector._y) && Utils::equal(_z, vector._z);
    }

    bool Vec3::operator!=(const Vec3 &vector) const {
        return !Utils::equal(_x, vector._x) && !Utils::equal(_y, vector._y) && !Utils::equal(_z, vector._z);
    }

} // tls
