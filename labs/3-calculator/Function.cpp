#include "Function.h"

using namespace std;

Function::Function(const shared_ptr<Variable>& operandPtr)
{
	m_firstOperand = operandPtr;
	operandPtr->AddDependentFunction(shared_ptr<Function>(this));
}

Function::Function(const shared_ptr<Function>& operandPtr)
{
	m_firstOperand = operandPtr;
	operandPtr->AddDependentFunction(shared_ptr<Function>(this));
}

Function::Function(
	const variant<shared_ptr<Variable>, shared_ptr<Function>>& firstOperand,
	Operation operation,
	const variant<shared_ptr<Variable>, shared_ptr<Function>>& secondOperand)
{
	if (holds_alternative<shared_ptr<Variable>>(firstOperand))
	{
		shared_ptr<Variable> operandPtr = get<shared_ptr<Variable>>(firstOperand);
		operandPtr->AddDependentFunction(shared_ptr<Function>(this));
		m_firstOperand = operandPtr;
	}
	else
	{
		shared_ptr<Function> operandPtr = get<shared_ptr<Function>>(firstOperand);
		operandPtr->AddDependentFunction(shared_ptr<Function>(this));
		m_firstOperand = operandPtr;
	}

	m_operation = operation;

	if (holds_alternative<shared_ptr<Variable>>(secondOperand))
	{
		shared_ptr<Variable> operandPtr = get<shared_ptr<Variable>>(secondOperand);
		operandPtr->AddDependentFunction(shared_ptr<Function>(this));
		m_secondOperand = operandPtr;
	}
	else
	{
		shared_ptr<Function> operandPtr = get<shared_ptr<Function>>(secondOperand);
		operandPtr->AddDependentFunction(shared_ptr<Function>(this));
		m_secondOperand = operandPtr;
	}
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

void Function::FlushCachedValue()
{
	m_cachedValue.reset();
}

void Function::AddDependentFunction(const shared_ptr<Function>& functionPtr)
{
	m_dependentFunctions.push_back(shared_ptr<Function>(functionPtr));
}

optional<double> Function::CalculateValue() const
{
	optional<double> value =
		holds_alternative<shared_ptr<Variable>>(m_firstOperand) ?
		get<shared_ptr<Variable>>(m_firstOperand)->GetValue() :
		get<shared_ptr<Function>>(m_firstOperand)->GetValue();

	if (!m_operation.has_value())
	{
		return value;
	}

	optional<double> secondOperandValue =
		holds_alternative<shared_ptr<Variable>>(m_firstOperand) ?
		get<shared_ptr<Variable>>(m_firstOperand)->GetValue() :
		get<shared_ptr<Function>>(m_firstOperand)->GetValue();

	if (!secondOperandValue.has_value())
	{
		return nullopt;
	}

	switch (*m_operation)
	{
	case Operation::Add:
		value = *value + *secondOperandValue;
	case Operation::Sub:
		value = *value - *secondOperandValue;
	case Operation::Mul:
		value = *value * *secondOperandValue;
	case Operation::Div:
		value = *value / *secondOperandValue;
	default:
		break;
	}

	return value;
}

void Function::FlushDependentFunctionValues() const
{
	for (shared_ptr<Function> dependentFn : m_dependentFunctions)
	{
		dependentFn->FlushCachedValue();
	}
}
