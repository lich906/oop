#pragma once
#include <optional>
#include <vector>

class Function;

class Operand
{
public:
	virtual double GetValue() const = 0;

	void AddDependentFunction(Function* functionPtr);

protected:
	~Operand() = default;

	void FlushDependentFunctionValues() const;

	std::vector<Function*> m_dependentFunctions;
};

#include "Function.h"
