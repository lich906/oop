#pragma once
#include <iostream>

class Complex
{
public:
	Complex(double real = 0.0, double imaginary = 0.0);

	double Re() const;
	double Im() const;
	double GetMagnitude() const;
	double GetArgument() const;

	Complex& operator+=(const Complex& rhs);
	Complex& operator-=(const Complex& rhs);
	Complex& operator*=(const Complex& rhs);
	Complex& operator/=(const Complex& rhs);

	Complex const operator-() const;
	Complex const operator+() const;

private:
	double m_real;
	double m_imaginary;

	Complex const GetInversion() const;
};

Complex const operator+(Complex lhs, const Complex& rhs);
Complex const operator-(Complex lhs, const Complex& rhs);
Complex const operator*(Complex lhs, const Complex& rhs);
Complex const operator/(Complex lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& stream, const Complex& complex);
std::istream& operator>>(std::istream& stream, Complex& complex);
