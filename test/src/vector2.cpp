#include "../include/vector2.hpp"

Vector2 Vector2::operator+(const Vector2 &vec) const
{
    return Vector2(x + vec.x, y + vec.y);
}

void Vector2::operator+=(const Vector2 &vec)
{
    x += vec.x, y += vec.y;
}

Vector2 Vector2::operator-(const Vector2 &vec) const
{
    return Vector2(x - vec.x, y - vec.y);
}

void Vector2::operator-=(const Vector2 &vec)
{
    x -= vec.x, y -= vec.y;
}

double Vector2::operator*(const Vector2 &vec) const
{
    return x * vec.x + y * vec.y;
}

Vector2 Vector2::operator*(double val) const
{
    return Vector2(x * val, y * val);
}

void Vector2::operator*=(double val)
{
    x *= val, y *= val;
}

bool Vector2::operator==(const Vector2 &vec) const
{
    return x == vec.x && y == vec.y;
}

bool Vector2::operator>(const Vector2 &vec) const
{
    return length() > vec.length();
}

bool Vector2::operator<(const Vector2 &vec) const
{
    return length() < vec.length();
}

double Vector2::length() const
{
    return sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() const
{
    double len = length();

    if (len == 0)
        return Vector2(0, 0);

    return Vector2(x / len, y / len);
}

bool Vector2::approx_zero() const
{
    return length() < 0.0001;
}