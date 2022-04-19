#include "Function.h"

using namespace std;

Function::Function(Operand* const operandPtr)
{
	operandPtr->AddDependentFunction(this);
	m_firstOperandPtr = operandPtr;
}

Function::Function(Operand* const firstOperandPtr, Operation operation, Operand* const secondOperandPtr)
{
	firstOperandPtr->AddDependentFunction(this);
	secondOperandPtr->AddDependentFunction(this);
	m_firstOperandPtr = firstOperandPtr;
	m_secondOperandPtr = secondOperandPtr;
	m_operation = operation;
}

double Function::GetValue() const
{
	if (m_cachedValue.has_value())
	{
		return *m_cachedValue;
	}

	FlushDependentFunctionValues();
	return *(m_cachedValue = CalculateValue());
}

void Function::FlushCachedValue()
{
	if (m_cachedValue.has_value())
	{
		m_cachedValue.reset();
		FlushDependentFunctionValues();
	}
}

double Function::CalculateValue() const
{
	double value = m_firstOperandPtr->GetValue();

	if (!m_operation.has_value() || isnan(value))
	{
		return value;
	}

	double secondOperandValue = (*m_secondOperandPtr)->GetValue();

	if (isnan(secondOperandValue))
	{
		return secondOperandValue;
	}

	switch (*m_operation)
	{
	case Operation::Add:
		return value + secondOperandValue;
	case Operation::Sub:
		return value - secondOperandValue;
	case Operation::Mul:
		return value * secondOperandValue;
	case Operation::Div:
		return value / secondOperandValue;
	default:
		return nan("");
	}
}
