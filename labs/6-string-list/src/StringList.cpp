#include "StringList.h"

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
	if (IsEmpty())
	{
		m_beginPtr = m_endPtr = new ListNode(data);
	}
	else
	{
		NodePtr newNodePtr = new ListNode(data);
		m_endPtr->next = newNodePtr;
		newNodePtr->prev = m_endPtr;
		m_endPtr = newNodePtr;
	}

	++m_length;

	return *this;
}

StringList& StringList::PushFront(const std::string& data)
{
	if (IsEmpty())
	{
		m_beginPtr = m_endPtr = new ListNode(data);
	}
	else
	{
		NodePtr newNodePtr = new ListNode(data);
		m_beginPtr->prev = newNodePtr;
		newNodePtr->next = m_beginPtr;
		m_beginPtr = newNodePtr;
	}

	++m_length;

	return *this;
}

StringList& StringList::PopBack()
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	NodePtr tmp = m_endPtr;
	m_endPtr = m_endPtr->prev;
	delete tmp;
	--m_length;

	if (IsEmpty())
		m_beginPtr = nullptr;

	return *this;
}

StringList& StringList::PopFront()
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	NodePtr tmp = m_beginPtr;
	m_beginPtr = m_beginPtr->next;
	delete tmp;
	--m_length;

	if (IsEmpty())
		m_endPtr = nullptr;

	return *this;
}

std::string StringList::GetBack() const
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	return m_endPtr->data;
}

std::string StringList::GetFront() const
{
	if (IsEmpty())
		throw std::logic_error("List is empty");

	return m_beginPtr->data;
}

void StringList::Clear() noexcept
{
	if (!IsEmpty())
	{
		NodePtr tmp;
		while ((tmp = m_beginPtr) != nullptr)
		{
			m_beginPtr = m_beginPtr->next;
			delete tmp;
		}
	}

	m_endPtr = nullptr;
	m_length = 0;
}

StringList::~StringList() noexcept
{
	Clear();
}
