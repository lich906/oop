#pragma once
#include <string>
#include <variant>
#include <memory>
#include <optional>
#include <vector>
class Variable;

class Function
{
public:
	enum class Operation
	{
		Add,
		Sub,
		Mul,
		Div
	};

	Function(const std::shared_ptr<Variable>& operandPtr);

	Function(const std::shared_ptr<Function>& operandPtr);

	Function(
		const std::variant<std::shared_ptr<Variable>, std::shared_ptr<Function>>& firstOperand,
		Operation operation,
		const std::variant<std::shared_ptr<Variable>, std::shared_ptr<Function>>& secondOperand);

	std::optional<double> GetValue() const;

	void FlushCachedValue();

	void AddDependentFunction(const std::shared_ptr<Function>& functionPtr);

private:
	mutable std::optional<double> m_cachedValue;

	std::optional<double> CalculateValue() const;

	void FlushDependentFunctionValues() const;

	std::variant<std::shared_ptr<Variable>, std::shared_ptr<Function>> m_firstOperand;
	std::optional<Operation> m_operation;
	std::variant<std::shared_ptr<Variable>, std::shared_ptr<Function>> m_secondOperand;

	std::vector<std::shared_ptr<Function>> m_dependentFunctions;
};

#include "Variable.h"
