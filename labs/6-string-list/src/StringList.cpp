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

StringList& StringList::PushBack(const std::string& data)
{
	Insert(cend(), data);

	return *this;
}

StringList& StringList::PushFront(const std::string& data)
{
	Insert(cbegin(), data);

	return *this;
}

StringList& StringList::PopBack()
{
	Erase(--cend());

	return *this;
}

StringList& StringList::PopFront()
{
	Erase(cbegin());

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

StringList::Iterator StringList::Insert(const ListBaseIterator& where, const std::string& data)
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

	return Iterator(newNodePtr);
}

StringList::Iterator StringList::Erase(const ListBaseIterator& where)
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	NodePtr wherePtr = where.m_nodePtr;

	if (wherePtr->next == nullptr || wherePtr->prev == nullptr)
		throw std::logic_error("Past-the-last element erase violation");

	NodePtr followingPtr;
	wherePtr->prev->next = followingPtr = wherePtr->next;
	wherePtr->next->prev = wherePtr->prev;

	if (wherePtr == m_beginPtr)
	{
		m_beginPtr = m_beginPtr->next;
	}

	delete wherePtr;
	--m_length;

	return Iterator(followingPtr);
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
	return ReverseIterator(m_endPtr->prev);
}

StringList::ReverseIterator StringList::rend()
{
	return ReverseIterator(m_beginPtr->prev);
}

StringList::ConstReverseIterator StringList::rbegin() const
{
	return ConstReverseIterator(m_endPtr->prev);
}

StringList::ConstReverseIterator StringList::rend() const
{
	return ConstReverseIterator(m_beginPtr->prev);
}

StringList::ConstReverseIterator StringList::crbegin() const
{
	return ConstReverseIterator(m_endPtr->prev);
}

StringList::ConstReverseIterator StringList::crend() const
{
	return ConstReverseIterator(m_beginPtr->prev);
}
