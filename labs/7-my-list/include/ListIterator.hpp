#pragma once
#include <iterator>
#include <stdexcept>
#include "ListNode.hpp"

template <typename T>
class MyList;

template <typename T>
class ListBaseIterator
{
public:
	friend class MyList<T>;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = size_t;

	bool operator!=(const ListBaseIterator& other) const
	{
		return m_nodePtr != other.m_nodePtr;
	}

	bool operator==(const ListBaseIterator& other) const
	{
		return !(*this != other);
	}

protected:
	ListBaseIterator()
		: m_nodePtr(nullptr)
	{
	}

	ListBaseIterator(NodePtr<T> data)
		: m_nodePtr(data)
	{
	}

	~ListBaseIterator() = default;

	T* operator->() const
	{
		if (m_nodePtr == nullptr)
			throw std::logic_error("Uninitialized iterator access violation");

		if (m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
			throw std::logic_error("Past-the-last element iterator access violation");

		return &(m_nodePtr->data);
	}

	T& operator*() const
	{
		if (m_nodePtr == nullptr)
			throw std::logic_error("Uninitialized iterator dereference violation");

		if (m_nodePtr->next == nullptr || m_nodePtr->prev == nullptr)
			throw std::logic_error("Past-the-last element iterator dereference violation");

		return m_nodePtr->data;
	}

	void operator++()
	{
		if (m_nodePtr == nullptr)
			throw std::logic_error("Uninitialized iterator increment violation");

		if (m_nodePtr->next == nullptr)
			throw std::logic_error("Past-the-last element iterator increment violation");

		m_nodePtr = m_nodePtr->next;
	}

	NodePtr<T> operator++(int)
	{
		if (m_nodePtr == nullptr)
			throw std::logic_error("Uninitialized iterator increment violation");

		if (m_nodePtr->next == nullptr)
			throw std::logic_error("Past-the-last element iterator increment violation");

		NodePtr<T> tmp = m_nodePtr;
		m_nodePtr = m_nodePtr->next;

		return tmp;
	}

	void operator--()
	{
		if (m_nodePtr == nullptr)
			throw std::logic_error("Uninitialized iterator decrement violation");

		if (m_nodePtr->prev == nullptr)
			throw std::logic_error("Reverse past-the-last element iterator decrement violation");

		m_nodePtr = m_nodePtr->prev;
	}

	NodePtr<T> operator--(int)
	{
		if (m_nodePtr == nullptr)
			throw std::logic_error("Uninitialized iterator decrement violation");

		if (m_nodePtr->prev == nullptr)
			throw std::logic_error("Reverse past-the-last element iterator decrement violation");

		NodePtr<T> tmp = m_nodePtr;
		m_nodePtr = m_nodePtr->prev;

		return tmp;
	}

	NodePtr<T> m_nodePtr;
};

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator : public ListBaseIterator<T>
{
public:
	using value_type = const T;
	using pointer = const T*;
	using reference = const T&;

	ListConstIterator()
		: ListBaseIterator<T>()
	{
	}

	ListConstIterator(NodePtr<T> data)
		: ListBaseIterator<T>(data)
	{
	}

	ListConstIterator(const ListIterator<T>& other)
		: ListBaseIterator<T>(other.m_nodePtr)
	{
	}

	pointer operator->() const
	{
		return ListBaseIterator<T>::operator->();
	}

	reference operator*() const
	{
		return ListBaseIterator<T>::operator*();
	}

	ListConstIterator& operator++()
	{
		ListBaseIterator<T>::operator++();
		return *this;
	}

	ListConstIterator operator++(int)
	{
		return ListConstIterator(ListBaseIterator<T>::operator++(1));
	}

	ListConstIterator& operator--()
	{
		ListBaseIterator<T>::operator--();
		return *this;
	}

	ListConstIterator operator--(int)
	{
		return ListConstIterator(ListBaseIterator<T>::operator--(1));
	}
};

template <typename T>
class ListIterator : public ListBaseIterator<T>
{
public:
	friend class ListConstIterator<T>;

	using value_type = T;
	using pointer = T*;
	using reference = T&;

	ListIterator()
		: ListBaseIterator<T>()
	{
	}

	ListIterator(NodePtr<T> data)
		: ListBaseIterator<T>(data)
	{
	}

	pointer operator->() const
	{
		return ListBaseIterator<T>::operator->();
	}

	reference operator*() const
	{
		return ListBaseIterator<T>::operator*();
	}

	ListIterator& operator++()
	{
		ListBaseIterator<T>::operator++();
		return *this;
	}

	ListIterator operator++(int)
	{
		return ListIterator(ListBaseIterator<T>::operator++(1));
	}

	ListIterator& operator--()
	{
		ListBaseIterator<T>::operator--();
		return *this;
	}

	ListIterator operator--(int)
	{
		return ListIterator(ListBaseIterator<T>::operator--(1));
	}
};
