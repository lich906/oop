#include "ListIterator.h"

bool ListBaseIterator::operator!=(const ListBaseIterator& other) const
{
	return m_nodePtr != other.m_nodePtr;
}

bool ListBaseIterator::operator==(const ListBaseIterator& other) const
{
	return !(*this != other);
}

std::string* ListBaseIterator::operator->() const
{
	if (m_nodePtr->next == nullptr)
		throw std::logic_error("Past-the-last element iterator access violation");

	return &(m_nodePtr->data);
}

std::string& ListBaseIterator::operator*() const
{
	if (m_nodePtr->next == nullptr)
		throw std::logic_error("Past-the-last element iterator dereference violation");

	return m_nodePtr->data;
}

void ListBaseIterator::operator++()
{
	if (m_nodePtr->next == nullptr)
		throw std::logic_error("Past-the-last element iterator increment violation");

	m_nodePtr = m_nodePtr->next;
}

NodePtr ListBaseIterator::operator++(int)
{
	if (m_nodePtr->next == nullptr)
		throw std::logic_error("Past-the-last element iterator increment violation");

	NodePtr tmp = m_nodePtr;
	m_nodePtr = m_nodePtr->next;

	return tmp;
}

void ListBaseIterator::operator--()
{
	if (m_nodePtr->prev == nullptr)
		throw std::logic_error("Reverse past-the-last element iterator decrement violation");

	m_nodePtr = m_nodePtr->prev;
}

NodePtr ListBaseIterator::operator--(int)
{
	if (m_nodePtr->prev == nullptr)
		throw std::logic_error("Reverse past-the-last element iterator decrement violation");

	NodePtr tmp = m_nodePtr;
	m_nodePtr = m_nodePtr->prev;

	return tmp;
}

ListBaseIterator::ListBaseIterator(NodePtr data)
	: m_nodePtr(data)
{
}

ListIterator::ListIterator(NodePtr data)
	: ListBaseIterator(data)
{
}

ListIterator::pointer ListIterator::operator->() const
{
	return ListBaseIterator::operator->();
}

ListIterator::reference ListIterator::operator*() const
{
	return ListBaseIterator::operator*();
}

ListIterator& ListIterator::operator++()
{
	ListBaseIterator::operator++();

	return *this;
}

ListIterator& ListIterator::operator++(int)
{
	ListIterator tmp(ListBaseIterator::operator++(1));

	return tmp;
}

ListIterator& ListIterator::operator--()
{
	ListBaseIterator::operator--();

	return *this;
}

ListIterator& ListIterator::operator--(int)
{
	ListIterator tmp(ListBaseIterator::operator--(1));

	return tmp;
}

ListConstIterator::ListConstIterator(NodePtr data)
	: ListBaseIterator(data)
{
}

ListConstIterator::ListConstIterator(const ListIterator& other)
	: ListBaseIterator(other.m_nodePtr)
{
}

ListConstIterator::pointer ListConstIterator::operator->() const
{
	return ListBaseIterator::operator->();
}

ListConstIterator::reference ListConstIterator::operator*() const
{
	return ListBaseIterator::operator*();
}

ListConstIterator& ListConstIterator::operator++()
{
	ListBaseIterator::operator++();

	return *this;
}

ListConstIterator& ListConstIterator::operator++(int)
{
	ListConstIterator tmp(ListBaseIterator::operator++(1));

	return tmp;
}

ListConstIterator& ListConstIterator::operator--()
{
	ListBaseIterator::operator--();

	return *this;
}

ListConstIterator& ListConstIterator::operator--(int)
{
	ListConstIterator tmp(ListBaseIterator::operator--(1));

	return tmp;
}
