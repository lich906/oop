#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>
#include "MyIterator.h"

class MyString
{
public:
	using const_iterator = MyConstIterator;
	using iterator = MyIterator;
	using const_reverse_iterator = std::reverse_iterator<MyConstIterator>;
	using reverse_iterator = std::reverse_iterator<MyIterator>;

	MyString();
	MyString(const char* pString);
	MyString(const char* pString, size_t length);
	MyString(const std::string& stlString);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;

	size_t GetLength() const;
	const char* GetStringData() const;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	MyString& operator+=(const MyString& other);

	const char operator[](size_t index) const;
	char& operator[](size_t index);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

private:
	void ExtendCapacity(size_t fitSize);
	size_t m_currentSize = 0;
	size_t m_currentCapacity = m_currentSize + 1;

	std::shared_ptr<char[]> m_stringData;
};

const MyString operator+(MyString lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);

std::ostream& operator<<(std::ostream& stream, const MyString& string);
std::istream& operator>>(std::istream& stream, MyString& string);
