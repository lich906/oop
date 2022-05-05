#include "MyString.h"

MyString::MyString()
	: m_stringData(new char[1]{ '\0' })
{
}

MyString::MyString(const char* pString)
	: m_currentSize(strlen(pString))
{
	m_stringData = new char[m_currentSize + 1];
	memcpy(m_stringData, pString, m_currentSize + 1);
}

MyString::MyString(const char* pString, size_t length)
	: m_currentSize(length)
{
	m_stringData = new char[m_currentSize + 1];
	memcpy(m_stringData, pString, m_currentSize);
	m_stringData[m_currentSize] = '\0';
}

MyString::MyString(const MyString& other)
	: m_currentSize(other.m_currentSize)
{
	m_stringData = new char[m_currentSize + 1];
	memcpy(m_stringData, other.m_stringData, m_currentSize);
	m_stringData[m_currentSize] = '\0';
}

MyString& MyString::operator=(const MyString& other)
{
	m_currentSize = other.m_currentSize;

	if (m_currentSize > m_currentCapacity)
	{
		delete[] m_stringData;
		m_stringData = new char[m_currentSize + 1];
		m_currentCapacity = m_currentSize;
	}

	memcpy(m_stringData, other.m_stringData, m_currentSize);
	m_stringData[m_currentSize] = '\0';

	return *this;
}

MyString::MyString(const std::string& stlString)
	: MyString(stlString.c_str(), stlString.size())
{
}

MyString::~MyString()
{
	delete[] m_stringData;
}

size_t MyString::GetLength() const
{
	return m_currentSize;
}

const char* MyString::GetStringData() const
{
	return m_stringData;
}
