#include "Variable.h"

void Variable::SetValue(double value)
{
	if (m_value != value)
	{
		FlushDependentFunctionValues();
		m_value = value;
	}
}

double Variable::GetValue() const
{
	return m_value;
}
