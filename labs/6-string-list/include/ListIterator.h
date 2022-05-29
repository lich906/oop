#pragma once
#include <iterator>
#include <stdexcept>
#include "ListNode.h"

class StringList;

class ListBaseIterator
{
public:
	friend StringList;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = size_t;

	bool operator!=(const ListBaseIterator& other) const;
	bool operator==(const ListBaseIterator& other) const;

protected:
	ListBaseIterator(NodePtr data);

	std::string* operator->() const;
	std::string& operator*() const;

	void operator++();
	NodePtr operator++(int);

	void operator--();
	NodePtr operator--(int);

	NodePtr m_nodePtr;
};

class ListIterator;

class ListConstIterator : public ListBaseIterator
{
public:
	using value_type = const std::string;
	using pointer = const std::string*;
	using reference = const std::string&;

	ListConstIterator(NodePtr data);
	ListConstIterator(const ListIterator& other);

	pointer operator->() const;

	reference operator*() const;

	ListConstIterator& operator++();
	ListConstIterator& operator++(int);

	ListConstIterator& operator--();
	ListConstIterator& operator--(int);
};

class ListIterator : public ListBaseIterator
{
public:
	friend ListConstIterator;

	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;

	ListIterator(NodePtr data);

	pointer operator->() const;

	reference operator*() const;

	ListIterator& operator++();
	ListIterator& operator++(int);

	ListIterator& operator--();
	ListIterator& operator--(int);
};