#include "StringList.h"

StringList::StringList()
	: m_beginPtr(new ListNode())
{
	try
	{
		m_endPtr = new ListNode();
	}
	catch (const std::bad_alloc&)
	{
		delete m_beginPtr;
		throw;
	}

	m_beginPtr->next = m_endPtr;
	m_endPtr->prev = m_beginPtr;
	m_beginPtr = m_endPtr;
}

StringList::~StringList() noexcept
{
	Clear();
	delete m_beginPtr->prev;
	delete m_endPtr;
}

bool StringList::IsEmpty() const
{
	return !m_length;
}

size_t StringList::GetLength() const
{
	return m_length;
}

void StringList::AddNodeToEmptyList(NodePtr newNodePtr)
{
	newNodePtr->prev = m_beginPtr->prev;
	newNodePtr->next = m_endPtr;
	m_beginPtr->prev->next = newNodePtr;
	m_endPtr->prev = newNodePtr;
	m_beginPtr = newNodePtr;
}

StringList& StringList::PushBack(const std::string& data)
{
	return Insert(cend(), data);
}

StringList& StringList::PushFront(const std::string& data)
{
	return Insert(cbegin(), data);
}

StringList& StringList::PopBack()
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	NodePtr tmp = m_endPtr->prev;

	tmp->prev->next = m_endPtr;
	m_endPtr->prev = tmp->prev;

	if (tmp == m_beginPtr)
	{
		m_beginPtr = m_endPtr;
	}

	delete tmp;
	--m_length;

	return *this;
}

StringList& StringList::PopFront()
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	NodePtr tmp = m_beginPtr;

	m_beginPtr->prev->next = m_beginPtr->next;
	m_beginPtr->next->prev = m_beginPtr->prev;
	m_beginPtr = m_beginPtr->next;

	delete tmp;
	--m_length;

	return *this;
}

const std::string& StringList::GetBack() const
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	return m_endPtr->prev->data;
}

const std::string& StringList::GetFront() const
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	return m_beginPtr->data;
}

StringList& StringList::Insert(const ConstIterator& where, const std::string& data)
{
	NodePtr newNodePtr = new ListNode(data);
	NodePtr wherePtr = where.m_nodePtr;

	newNodePtr->next = wherePtr;
	newNodePtr->prev = wherePtr->prev;
	wherePtr->prev->next = newNodePtr;
	wherePtr->prev = newNodePtr;

	if (wherePtr == m_beginPtr)
	{
		m_beginPtr = newNodePtr;
	}

	++m_length;

	return *this;
}

void StringList::Clear() noexcept
{
	if (!IsEmpty())
	{
		m_beginPtr->prev->next = m_endPtr;
		m_endPtr->prev = m_beginPtr->prev;

		NodePtr tmp;
		while ((tmp = m_beginPtr) != m_endPtr)
		{
			m_beginPtr = m_beginPtr->next;
			delete tmp;
		}

		m_length = 0;
	}
}

StringList::Iterator StringList::begin()
{
	return Iterator(m_beginPtr);
}

StringList::Iterator StringList::end()
{
	return Iterator(m_endPtr);
}

StringList::ConstIterator StringList::begin() const
{
	return ConstIterator(m_beginPtr);
}

StringList::ConstIterator StringList::end() const
{
	return ConstIterator(m_endPtr);
}

StringList::ConstIterator StringList::cbegin() const
{
	return ConstIterator(m_beginPtr);
}

StringList::ConstIterator StringList::cend() const
{
	return ConstIterator(m_endPtr);
}

StringList::ReverseIterator StringList::rbegin()
{
	return std::make_reverse_iterator(end());
}

StringList::ReverseIterator StringList::rend()
{
	return std::make_reverse_iterator(begin());
}

StringList::ConstReverseIterator StringList::rbegin() const
{
	return std::make_reverse_iterator(end());
}

StringList::ConstReverseIterator StringList::rend() const
{
	return std::make_reverse_iterator(begin());
}

StringList::ConstReverseIterator StringList::crbegin() const
{
	return std::make_reverse_iterator(end());
}

StringList::ConstReverseIterator StringList::crend() const
{
	return std::make_reverse_iterator(begin());
}
