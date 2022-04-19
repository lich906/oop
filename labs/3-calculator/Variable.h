#pragma once
#include "Function.h"

class Variable : public Operand
{
public:
	Variable(double value)
		: m_value(value)
	{
	}

	void SetValue(double value);

	double GetValue() const override;

private:
	double m_value;
};
