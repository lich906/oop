#include "Operand.h"

void Operand::AddDependentFunction(Function* functionPtr)
{
	m_dependentFunctions.push_back(functionPtr);
}

void Operand::FlushDependentFunctionValues() const
{
	for (const Function* const dependentFn : m_dependentFunctions)
	{
		dependentFn->FlushCachedValue();
	}
}