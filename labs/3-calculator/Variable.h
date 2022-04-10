#pragma once
#include "Function.h"

class Variable
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

	std::optional<double> GetValue() const;

	void AddDependentFunction(const std::shared_ptr<Function>& function);

private:
	void FlushDependentFunctionValues() const;

	std::optional<double> m_value;
	std::vector<std::shared_ptr<Function>> m_dependentFunctions;
};
