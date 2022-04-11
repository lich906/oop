#include "Function.h"

using namespace std;

Function::Function(Operand* const operandPtr)
{
	m_firstOperandPtr = operandPtr;
	operandPtr->AddDependentFunction(this);
}

Function::Function(Operand* const firstOperandPtr, Operation operation, Operand* const secondOperandPtr)
{
	firstOperandPtr->AddDependentFunction(this);
	secondOperandPtr->AddDependentFunction(this);
	m_firstOperandPtr = firstOperandPtr;
	m_secondOperandPtr = secondOperandPtr;
	m_operation = operation;
}

optional<double> Function::GetValue() const
{
	if (m_cachedValue.has_value())
	{
		return *m_cachedValue;
	}

	optional<double> newValue = CalculateValue();

	if (newValue.has_value())
	{
		FlushDependentFunctionValues();
		return *(m_cachedValue = newValue);
	}

	return nullopt;
}

void Function::FlushCachedValue() const
{
	if (m_cachedValue.has_value())
	{
		m_cachedValue.reset();
		FlushDependentFunctionValues();
	}
}

optional<double> Function::CalculateValue() const
{
	optional<double> value = m_firstOperandPtr->GetValue();

	if (!m_operation.has_value() || !value.has_value())
	{
		return value;
	}

	optional<double> secondOperandValue = (*m_secondOperandPtr)->GetValue();

	if (!secondOperandValue.has_value())
	{
		return nullopt;
	}

	switch (*m_operation)
	{
	case Operation::Add:
		return *value + *secondOperandValue;
	case Operation::Sub:
		return *value - *secondOperandValue;
	case Operation::Mul:
		return *value * *secondOperandValue;
	case Operation::Div:
		return *value / *secondOperandValue;
	default:
		return nullopt;
	}
}
