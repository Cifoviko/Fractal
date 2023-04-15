#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex
{
private:

public:
    Complex pow(int n);
    Complex* operator*=(const Complex& c);
    friend Complex operator*(const Complex& a, const Complex& b);
    Complex* operator+=(const Complex& c);
    friend Complex operator+(const Complex& a, const Complex& b);
    Complex* operator-=(const Complex& c);
    Complex* operator-();
    friend Complex operator-(const Complex& a, const Complex& b);
    long double x, y;
    Complex();
    Complex(long double x);
    Complex(long double x, long double y);
};

#endif // COMPLEX_H
