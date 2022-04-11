#pragma once
#include "Function.h"

class Variable : public Operand
{
public:
	Variable()
	{
	}
	
	Variable(const std::optional<double>& value)
		: m_value(value)
	{
	}

	void SetValue(std::optional<double> value);

	std::optional<double> GetValue() const override;

private:
	std::optional<double> m_value;
};
