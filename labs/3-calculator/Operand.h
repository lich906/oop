#pragma once
#include <optional>
#include <vector>

class Function;

class Operand
{
public:
	virtual std::optional<double> GetValue() const = 0;

	void AddDependentFunction(Function* functionPtr);

protected:
	void FlushDependentFunctionValues() const;

	std::vector<Function*> m_dependentFunctions;
};

#include "Function.h"
