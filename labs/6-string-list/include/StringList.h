#pragma once
#include "ListIterator.h"

class StringList
{
public:
	using Iterator = ListIterator;
	using ConstIterator = ListConstIterator;
	using ReverseIterator = ListReverseIterator;
	using ConstReverseIterator = ListConstReverseIterator;

	StringList();
	StringList(StringList&&) = default;
	StringList(const StringList&) = delete; // реализовать и оператор
	
	~StringList() noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

	bool IsEmpty() const;
	operator bool() const { return !IsEmpty(); }

	size_t GetLength() const;

	StringList& PushBack(const std::string& data);
	StringList& PushFront(const std::string& data);

	StringList& PopBack();
	StringList& PopFront();

	const std::string& GetBack() const;
	const std::string& GetFront() const;

	Iterator Insert(const ListBaseIterator& where, const std::string& data);
	Iterator Erase(const ListBaseIterator& where);

	void Clear() noexcept;

private:
	NodePtr m_beginPtr = nullptr;
	NodePtr m_endPtr = nullptr;
	size_t m_length = 0;
};
