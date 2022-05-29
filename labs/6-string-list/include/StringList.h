#pragma once
#include "ListIterator.h"

class StringList
{
public:
	using Iterator = ListIterator;
	using ConstIterator = ListConstIterator;
	using ReverseIterator = std::reverse_iterator<ListIterator>;
	using ConstReverseIterator = std::reverse_iterator<ListConstIterator>;

	StringList();
	StringList(StringList&&) = default;
	StringList(const StringList&) = delete;

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

	void Clear() noexcept;

private:
	void AddNodeToEmptyList(NodePtr newNodePtr);

	NodePtr m_beginPtr = nullptr;
	NodePtr m_endPtr = nullptr;
	size_t m_length = 0;
};
