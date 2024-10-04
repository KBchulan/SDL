#ifndef VECTOR2_HPP
#define VECTOR2_HPP

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

    double operator*=(double);

    bool operator==(const Vector2 &vec) const;

    bool operator>(const Vector2 &vec) const;

    bool operator<(const Vector2 &vec) const;

    double length() const;
};

#endif // VECTOR2_HPP