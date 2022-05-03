#include "MyString.h"

MyString::MyString()
	: m_currentSize(0)
	, m_stringData(new char[1]{ '\0' })
{
}

MyString::~MyString()
{
	delete[] m_stringData;
}

const char* MyString::GetStringData() const
{
	return m_stringData;
}
