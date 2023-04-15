#include "complex.h"

Complex::Complex() : x(0), y(0) {}

Complex::Complex(long double x) : x(x), y(0) {}

Complex::Complex(long double x, long double y) : x(x), y(y) {}

Complex Complex::pow(int n)
{
    Complex res = Complex(1, 0);
    Complex r = Complex(this->x, this->y);
    if(n < 0)
    {
        n = abs(n);
        r.x /= (x * x + y * y);
        r.y /= (x * x + y * y);
        r.y = -r.y;
    }
    while(n > 0)
    {
        if((n & 1) == 1)
        {
            res *= r;
        }
        r *= r;
        n >>= 1;
    }

    return res;
}

Complex* Complex::operator*=(const Complex& c)
{
    long double x = this->x * c.x - this->y * c.y;
    long double y = this->x * c.y + this->y * c.x;
    this->x = x;
    this->y = y;
    return this;
}

Complex* Complex::operator+=(const Complex& c)
{
    this->x += c.x;
    this->y += c.y;
    return this;
}

Complex* Complex::operator-=(const Complex& c)
{
    this->x -= c.x;
    this->y -= c.y;
    return this;
}

Complex* Complex::operator-()
{
    this->x = -this->x;
    this->y = -this->y;
    return this;
}

Complex operator*(const Complex& a, const Complex& b)
{
    return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.y);
}

Complex operator+(const Complex& a, const Complex& b)
{
    return Complex(a.x + b.x, a.y + b.y);
}

Complex operator-(const Complex& a, const Complex& b)
{
    return Complex(a.x - b.x, a.y - b.y);
}
