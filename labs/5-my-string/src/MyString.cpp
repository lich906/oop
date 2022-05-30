#include "MyString.h"

MyString::MyString()
	: m_stringData(InitStringData())
{
}

MyString::MyString(const char* pString)
	: m_currentSize(strlen(pString))
{
	m_stringData = std::make_unique<char[]>(m_currentCapacity);
	memcpy(m_stringData.get(), pString, m_currentSize + 1);
}

MyString::MyString(const char* pString, size_t length)
	: m_currentSize(length)
{
	m_stringData = std::make_unique<char[]>(m_currentCapacity);
	memcpy(m_stringData.get(), pString, m_currentSize);
	m_stringData[m_currentSize] = '\0';
}

MyString::MyString(const MyString& other)
	: m_currentSize(other.GetLength())
	, m_currentCapacity(other.m_currentCapacity)
{
	m_stringData = std::make_unique<char[]>(m_currentCapacity);
	memcpy(m_stringData.get(), other.GetStringData(), m_currentSize);
	m_stringData[m_currentSize] = '\0';
}

MyString::MyString(MyString&& other) noexcept
	: m_stringData(InitStringData())
{
	std::swap(other.m_currentSize, m_currentSize);
	std::swap(other.m_currentCapacity, m_currentCapacity);
	std::swap(other.m_stringData, m_stringData);
}

MyString::MyString(const std::string& stlString)
	: MyString(stlString.c_str(), stlString.size())
{
}

MyString& MyString::operator=(const MyString& other)
{
	// сделать строгую гарантию без. искл
	// проверка на самоприсваивание
	if (m_stringData == other.m_stringData)
	{
		return *this;
	}

	if (other.GetLength() >= m_currentCapacity)
	{
		size_t extendedCapacity = ExtendCapacity(other.GetLength());
		m_stringData = std::make_unique<char[]>(extendedCapacity);
		m_currentCapacity = extendedCapacity;
	}

	m_currentSize = other.GetLength();

	memcpy(m_stringData.get(), other.GetStringData(), m_currentSize);
	m_stringData[m_currentSize] = '\0';

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	m_currentSize = 0;
	m_currentCapacity = 1;
	m_stringData = InitStringData();

	std::swap(other.m_currentSize, m_currentSize);
	std::swap(other.m_currentCapacity, m_currentCapacity);
	std::swap(other.m_stringData, m_stringData);

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
		size_t extendedCapacity = ExtendCapacity(other.GetLength() + m_currentSize);
		// можно использовать make_shared
		// строгая гарантия безоп. искл.
		auto newArray = std::make_unique<char[]>(extendedCapacity);
		memcpy(newArray.get(), GetStringData(), m_currentSize);
		memcpy(newArray.get() + m_currentSize, other.GetStringData(), other.GetLength());
		m_stringData = std::move(newArray);
		m_currentCapacity = extendedCapacity;
	}
	else
	{
		memcpy(m_stringData.get() + m_currentSize, other.GetStringData(), other.GetLength());
	}

	m_currentSize += other.GetLength();
	m_stringData[m_currentSize] = '\0';

	return *this;
}


// возвращать const&
const char MyString::operator[](size_t index) const
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

MyString::iterator MyString::begin()
{
	return iterator(m_stringData.get());
}

MyString::iterator MyString::end()
{
	return iterator(m_stringData.get() + m_currentSize);
}

MyString::const_iterator MyString::begin() const
{
	return const_iterator(m_stringData.get());
}

MyString::const_iterator MyString::end() const
{
	return const_iterator(m_stringData.get() + m_currentSize);
}

MyString::const_iterator MyString::cbegin() const
{
	return const_iterator(m_stringData.get());
}

MyString::const_iterator MyString::cend() const
{
	return const_iterator(m_stringData.get() + m_currentSize);
}

MyString::reverse_iterator MyString::rbegin()
{
	return std::make_reverse_iterator(end());
}

MyString::reverse_iterator MyString::rend()
{
	return std::make_reverse_iterator(begin());
}

MyString::const_reverse_iterator MyString::rbegin() const
{
	return std::make_reverse_iterator(end());
}

MyString::const_reverse_iterator MyString::rend() const
{
	return std::make_reverse_iterator(begin());
}

MyString::const_reverse_iterator MyString::crbegin() const
{
	return std::make_reverse_iterator(cend());
}

MyString::const_reverse_iterator MyString::crend() const
{
	return std::make_reverse_iterator(cbegin());
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
	m_currentSize = 0; // просто обнулять size
	m_stringData[0] = '\0';
}

size_t MyString::ExtendCapacity(size_t fitSize)
{
	size_t capacity = m_currentCapacity;
	while (capacity <= fitSize && capacity != 0xFFFFFFFF)
	{
		if (capacity & 0x80000000)
		{
			capacity |= capacity >> 1;
		}
		else
		{
			capacity <<= 1;
		}
	}
	return capacity;
}

size_t MyString::InitCapacity(size_t fitSize)
{
	size_t capacity = 1;
	while (fitSize)
	{
		capacity <<= 1;
		fitSize >>= 1;
	}
	return capacity;
}

std::unique_ptr<char[]> MyString::InitStringData()
{
	auto ptr = std::make_unique<char[]>(1);
	ptr[0] = '\0';
	return ptr;
}

const MyString operator+(MyString lhs, const MyString& rhs)
{
	return lhs += rhs;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}

	return memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	// не будет работать на "канал-канализация"
	return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return rhs < lhs;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs > rhs);
}

std::ostream& operator<<(std::ostream& stream, const MyString& string)
{
	for (size_t index = 0, length = string.GetLength(); index < length && stream; ++index)
		stream << string[index];

	return stream;
}

std::istream& operator>>(std::istream& stream, MyString& string)
{
	char ch;
	std::vector<char> buffer;

	if (stream.flags() & std::ios_base::skipws)
	{
		while (std::isspace(stream.peek()))
			stream.get();
	}

	while (!std::isspace(stream.peek()) && stream.get(ch))
		buffer.push_back(ch);

	if (buffer.empty())
	{
		stream.setstate(std::ios_base::failbit);
		return stream;
	}

	string = MyString(buffer.data(), buffer.size());

	return stream;
}
