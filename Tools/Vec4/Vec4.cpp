/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Vec4
*/

#include <complex>
#include "Vec4.hpp"
#include "Utils.hpp"

namespace tls {

    Vec4::Vec4() {
        _x = 0;
        _y = 0;
        _z = 0;
        _a = 0;
    }

    Vec4::Vec4(double x, double y, double z, double a) {
        _x = x;
        _y = y;
        _z = z;
        _a = a;
    }

    Vec4::Vec4(const Vec4 &vector) {
        _x = vector._x;
        _y = vector._y;
        _z = vector._z;
        _a = vector._a;
    }

    double Vec4::length() const {
        return std::sqrt(static_cast<double>(_x * _x) + static_cast<double>(_y * _y) + static_cast<double>(_z * _z) + static_cast<double>(_a * _a));
    }

    Vec4 Vec4::operator+(const Vec4 &vector) const {
        Vec4 result;

        result._x = _x + vector._x;
        result._y = _y + vector._y;
        result._z = _z + vector._z;
        result._a = _a + vector._a;
        return result;
    }

    Vec4 &Vec4::operator+=(const Vec4 &vector) {
        _x += vector._x;
        _y += vector._y;
        _z += vector._z;
        _a += vector._a;
        return *this;
    }

    Vec4 Vec4::operator-(const Vec4 &vector) const {
        Vec4 result;

        result._x = _x - vector._x;
        result._y = _y - vector._y;
        result._z = _z - vector._z;
        result._a = _a - vector._a;
        return result;
    }

    Vec4 &Vec4::operator-=(const Vec4 &vector) {
        _x -= vector._x;
        _y -= vector._y;
        _z -= vector._z;
        _a -= vector._a;
        return *this;
    }

    Vec4 Vec4::operator*(const Vec4 &vector) const {
        Vec4 result;

        result._x = _x * vector._x;
        result._y = _y * vector._y;
        result._z = _z * vector._z;
        result._a = _a * vector._a;
        return result;
    }

    Vec4 &Vec4::operator*=(const Vec4 &vector) {
        _x *= vector._x;
        _y *= vector._y;
        _z *= vector._z;
        _a *= vector._a;
        return *this;
    }

    Vec4 Vec4::operator/(const Vec4 &vector) const {
        Vec4 result;

        result._x = _x / vector._x;
        result._y = _y / vector._y;
        result._z = _z / vector._z;
        result._a = _a / vector._a;
        return result;
    }

    Vec4 &Vec4::operator/=(const Vec4 &vector) {
        _x /= vector._x;
        _y /= vector._y;
        _z /= vector._z;
        _a /= vector._a;
        return *this;
    }

    Vec4 Vec4::operator*(double value) const {
        Vec4 result;

        result._x = _x * value;
        result._y = _y * value;
        result._z = _z * value;
        result._a = _a * value;
        return result;
    }

    Vec4 &Vec4::operator*=(double value) {
        _x *= value;
        _y *= value;
        _z *= value;
        _a *= value;
        return *this;
    }

    Vec4 Vec4::operator/(double value) const {
        Vec4 result;

        result._x = _x / value;
        result._y = _y / value;
        result._z = _z / value;
        result._a = _a / value;
        return result;
    }

    Vec4 &Vec4::operator/=(double value) {
        _x /= value;
        _y /= value;
        _z /= value;
        _a /= value;
        return *this;
    }

    double Vec4::dot(const Vec4 &vector) const {
        return (_x * vector._x) + (_y * vector._y) + (_z * vector._z) + (_a * vector._a);
    }

    Vec4::Vec4(const Vec4 &point1, const Vec4 &point2) {
        _x = point2._x - point1._x;
        _y = point2._y - point1._y;
        _z = point2._z - point1._z;
        _a = point2._a - point1._a;
    }

    Vec4 Vec4::operator+(double value) const {
        Vec4 result;

        result._x = _x + value;
        result._y = _y + value;
        result._z = _z + value;
        result._a = _a + value;
        return result;
    }

    Vec4 &Vec4::operator+=(double value) {
        _x += value;
        _y += value;
        _z += value;
        _a += value;
        return *this;
    }

    Vec4 Vec4::normalized() const {
        double len = std::sqrt(dot(*this));

        tls::Vec4 normal(_x / len, _y / len, _z / len, _a /len);
        return normal;
    }

    bool Vec4::operator==(const Vec4 &vector) const {
        return Utils::equal(_x, vector._x) && Utils::equal(_y, vector._y) && Utils::equal(_z, vector._z) && Utils::equal(_a, vector._a);
    }

} // tls