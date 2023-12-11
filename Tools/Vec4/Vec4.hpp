//
// Created by noah on 12/11/23.
//

#ifndef RTYPE_VEC4_HPP
#define RTYPE_VEC4_HPP

namespace tls {
    class Vec4 {
        public:
            // Constructors
            Vec4();
            Vec4(double x, double y, double z, double a);
            Vec4(const Vec4 &vector);
            Vec4(Vec4 &&vector) = default;
            Vec4(const Vec4 &point1, const Vec4 &point2);

            // Destructor
            ~Vec4() = default;

            // Operators
            Vec4 &operator=(const Vec4 &vector) = default;
            Vec4 &operator=(Vec4 &&vector) = default;

            Vec4 operator+(const Vec4 &vector) const;
            Vec4 &operator+=(const Vec4 &vector);
            Vec4 operator-(const Vec4 &vector) const;
            Vec4 &operator-=(const Vec4 &vector);
            Vec4 operator*(const Vec4 &vector) const;
            Vec4 &operator*=(const Vec4 &vector);
            Vec4 operator/(const Vec4 &vector) const;
            Vec4 &operator/=(const Vec4 &vector);

            Vec4 operator*(double value) const;
            Vec4 operator+(double value) const;
            Vec4 &operator*=(double value);
            Vec4 &operator+=(double value);
            Vec4 operator/(double value) const;
            Vec4 &operator/=(double value);

            bool operator==(const Vec4 &vector) const;

            Vec4 normalized() const;

            // Methods
            double dot(const Vec4 &vector) const;
            double length() const;

            // Variables
            double _x;
            double _y;
            double _z;
            double _a;
    };

} // tls

#endif //RTYPE_VEC4_HPP
