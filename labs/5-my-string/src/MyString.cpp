#include "MyString.h"
#include <stdexcept>

MyString::MyString()
	: m_stringData(std::shared_ptr<char[]>(new char[1]{ '\0' }))
{
}

MyString::MyString(const char* pString)
	: m_currentSize(strlen(pString))
{
	m_stringData = std::shared_ptr<char[]>(new char[m_currentCapacity]);
	memcpy(m_stringData.get(), pString, m_currentCapacity);
}

MyString::MyString(const char* pString, size_t length)
	: m_currentSize(length)
{
	m_stringData = std::shared_ptr<char[]>(new char[m_currentCapacity]);
	memcpy(m_stringData.get(), pString, m_currentSize);
	m_stringData[m_currentSize] = '\0';
}

MyString::MyString(const MyString& other)
	: m_currentSize(other.GetLength())
	, m_currentCapacity(other.m_currentCapacity)
{
	if (m_stringData == other.m_stringData)
	{
		return;
	}

	m_stringData = std::shared_ptr<char[]>(new char[m_currentCapacity]);
	memcpy(m_stringData.get(), other.GetStringData(), m_currentSize);
	m_stringData[m_currentSize] = '\0';
}

MyString::MyString(MyString&& other) noexcept
	: m_currentSize(other.m_currentSize)
	, m_currentCapacity(other.m_currentCapacity)
	, m_stringData(other.m_stringData)
{
	other.m_stringData = nullptr;
}

MyString::MyString(const std::string& stlString)
	: MyString(stlString.c_str(), stlString.size())
{
}

MyString& MyString::operator=(const MyString& other)
{
	m_currentSize = other.GetLength();

	if (m_currentSize > m_currentCapacity)
	{
		ExtendCapacity(m_currentSize);
		m_stringData = std::shared_ptr<char[]>(new char[m_currentCapacity]);
	}

	memcpy(m_stringData.get(), other.GetStringData(), m_currentSize);
	m_stringData[m_currentSize] = '\0';

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	m_currentSize = other.GetLength();
	m_currentCapacity = other.m_currentCapacity;
	m_stringData = other.m_stringData;

	return *this;
}

MyString& MyString::operator+=(const MyString& other)
{
	if (!other.GetLength())
	{
		return *this;
	}

	if (other.GetLength() + m_currentSize >= m_currentCapacity)
	{
		ExtendCapacity(other.GetLength() + m_currentSize);
		auto newArray = std::shared_ptr<char[]>(new char[m_currentCapacity]);
		memcpy(newArray.get(), GetStringData(), m_currentSize);
		memcpy(newArray.get() + m_currentSize, other.GetStringData(), other.GetLength());
		m_stringData = newArray;
	}
	else
	{
		memcpy(m_stringData.get() + m_currentSize, other.GetStringData(), other.GetLength());
	}

	m_currentSize += other.GetLength();
	m_stringData[m_currentSize] = '\0';

	return *this;
}

char const MyString::operator[](size_t index) const
{
	if (index >= m_currentSize)
	{
		throw std::out_of_range("Out of range element access");
	}

	return m_stringData[index];
}

char& MyString::operator[](size_t index)
{
	if (index >= m_currentSize)
	{
		throw std::out_of_range("Out of range element access");
	}

	return m_stringData[index];
}

size_t MyString::GetLength() const
{
	return m_currentSize;
}

const char* MyString::GetStringData() const
{
	return m_stringData.get();
}

MyString MyString::SubString(size_t start, size_t length) const
{
	if (start >= m_currentSize || !length)
	{
		return MyString();
	}

	if (!start && length >= m_currentSize)
	{
		return *this;
	}

	if (length + start > m_currentSize)
	{
		return MyString(m_stringData.get() + start, m_currentSize - start);
	}
	else
	{
		return MyString(m_stringData.get() + start, length);
	}
}

void MyString::Clear()
{
	m_stringData = std::shared_ptr<char[]>(new char[1]{ '\0' });
	m_currentSize = 0;
	m_currentCapacity = 1;
}

void MyString::ExtendCapacity(size_t fitSize)
{
	while (m_currentCapacity <= fitSize)
		m_currentCapacity <<= 1;
}

MyString const operator+(MyString lhs, const MyString& rhs)
{
	return lhs += rhs;
}

bool const operator==(const MyString& lhs, const MyString& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}

	return memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) == 0;
}

bool const operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool const operator<(const MyString& lhs, const MyString& rhs)
{
	if (lhs.GetLength() >= rhs.GetLength())
	{
		return memcmp(lhs.GetStringData(), rhs.GetStringData(), rhs.GetLength()) < 0;
	}
	else
	{
		return memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) <= 0;
	}
}

bool const operator>(const MyString& lhs, const MyString& rhs)
{
	if (lhs.GetLength() <= rhs.GetLength())
	{
		return memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) > 0;
	}
	else
	{
		return memcmp(lhs.GetStringData(), rhs.GetStringData(), rhs.GetLength()) >= 0;
	}
}

bool const operator>=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs < rhs);
}

bool const operator<=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs > rhs);
}
