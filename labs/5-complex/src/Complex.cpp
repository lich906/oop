#include "Complex.h"
#include <math.h>
#include <stdexcept>

Complex::Complex(double real, double imaginary)
	: m_real(real)
	, m_imaginary(imaginary)
{
}

double Complex::Re() const
{
	return m_real;
}

double Complex::Im() const
{
	return m_imaginary;
}

double Complex::GetMagnitude() const
{
	return hypot(m_real, m_imaginary);
}

double Complex::GetArgument() const
{
	return (m_imaginary >= 0) ? acos(m_real / GetMagnitude()) : -acos(m_real / GetMagnitude());
}

Complex& Complex::operator+=(const Complex& rhs)
{
	m_real += rhs.Re();
	m_imaginary += rhs.Im();

	return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
	m_real -= rhs.Re();
	m_imaginary -= rhs.Im();

	return *this;
}

Complex& Complex::operator*=(const Complex& rhs)
{
	double oldReal = m_real;
	m_real = m_real * rhs.Re() - m_imaginary * rhs.Im();
	m_imaginary = m_imaginary * rhs.Re() + oldReal * rhs.Im();

	return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
	if (rhs.GetMagnitude() == 0)
	{
		throw std::logic_error("Divide by zero");
	}

	return *this *= rhs.GetInversion();
}

Complex const Complex::operator-() const
{
	return Complex(-m_real, -m_imaginary);
}

Complex const Complex::operator+() const
{
	return *this;
}

Complex const Complex::GetInversion() const
{
	double divisor = m_real * m_real + m_imaginary * m_imaginary;
	return Complex(m_real / divisor, -m_imaginary / divisor);
}

Complex const operator+(Complex lhs, const Complex& rhs)
{
	return lhs += rhs;
}

Complex const operator-(Complex lhs, const Complex& rhs)
{
	return lhs -= rhs;
}

Complex const operator*(Complex lhs, const Complex& rhs)
{
	return lhs *= rhs;
}

Complex const operator/(Complex lhs, const Complex& rhs)
{
	try
	{
		return lhs /= rhs;
	}
	catch(const std::logic_error&)
	{
		throw;
	}
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
	return (std::fabs(lhs.Re() - rhs.Re()) < FLT_EPSILON) && (std::fabs(lhs.Im() - rhs.Im()) < FLT_EPSILON);
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const Complex& complex)
{
	stream << complex.Re();

	if (complex.Im() >= 0)
	{
		stream << '+';
	}

	return stream << complex.Im() << 'i';
}

std::istream& operator>>(std::istream& stream, Complex& complex)
{
	double re;

	if (stream >> re)
	{
		double im;
		if (stream >> std::noskipws >> im)
		{
			if (stream.peek() == 'i')
			{
				stream.get();
				complex = Complex(re, im);
			}
			else
			{
				complex = Complex(re);
			}
		}
		else
		{
			complex = Complex(re);
		}

		stream >> std::skipws;
	}
	return stream;
}