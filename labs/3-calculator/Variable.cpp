#include "Variable.h"

void Variable::SetValue(std::optional<double> value)
{
	if (!value.has_value())
	{
		if (m_value.has_value())
		{
			FlushDependentFunctionValues();
			m_value.reset();
		}
	}
	else if (!m_value.has_value() || *m_value != value)
	{
		FlushDependentFunctionValues();
		m_value = value;
	}
}

std::optional<double> Variable::GetValue() const
{
	return m_value;
}

void Variable::AddDependentFunction(const std::shared_ptr<Function>& functionPtr)
{
	m_dependentFunctions.push_back(std::shared_ptr<Function>(functionPtr));
}

void Variable::FlushDependentFunctionValues() const
{
	for (std::shared_ptr<Function> dependentFn : m_dependentFunctions)
	{
		dependentFn->FlushCachedValue();
	}
}
