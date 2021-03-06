#pragma once
#include "Operand.h"
#include <string>
#include <variant>
#include <memory>
class Variable;

class Function : public Operand
{
public:
	enum class Operation
	{
		Add,
		Sub,
		Mul,
		Div
	};

	Function(Operand* const operandPtr);

	Function(Operand* const firstVarPtr, Operation operation, Operand* const secondVarPtr);

	double GetValue() const override;

	void FlushCachedValue();

private:
	mutable std::optional<double> m_cachedValue;

	double CalculateValue() const;

	Operand* m_firstOperandPtr;
	std::optional<Operation> m_operation;
	std::optional<Operand*> m_secondOperandPtr;
};

#include "Variable.h"
