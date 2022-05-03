#pragma once
#include <string>

class MyString
{
public:
	MyString();

	MyString(const char* pString);

	MyString(const char* pString, size_t length);

	MyString(const MyString& other);

	MyString(MyString&& other);

	MyString(const std::string& stlString);

	~MyString();

	size_t GetLength() const;

	const char* GetStringData() const;

	MyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

private:
	size_t m_currentSize;

	char* m_stringData;
};
