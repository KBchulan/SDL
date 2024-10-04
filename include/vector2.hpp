#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>

class Vector2
{
public:
    double x = 0;
    double y = 0;

public:
    Vector2() = default;
    ~Vector2() = default;

    Vector2(double x, double y)
        : x(x), y(y) {}

    Vector2 operator+(const Vector2 &vec) const;

    void operator+=(const Vector2 &vec);

    Vector2 operator-(const Vector2 &vec) const;

    void operator-=(const Vector2 &vec);

    double operator*(const Vector2 &vec) const;

    Vector2 operator*(double val) const;

    void operator*=(double val);

    bool operator==(const Vector2 &vec) const;

    bool operator>(const Vector2 &vec) const;

    bool operator<(const Vector2 &vec) const;

    double length() const;

    Vector2 normalize() const;

    bool approx_zero() const;
};

#endif // VECTOR2_HPP