#pragma once
#include "ListIterator.hpp"

template <typename T>
class MyList
{
public:
	using Iterator = ListIterator<T>;
	using ConstIterator = ListConstIterator<T>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	MyList()
		: m_beginPtr(new ListNode<T>())
	{
		try
		{
			m_endPtr = new ListNode<T>();
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

	MyList(MyList&&) = default;
	MyList& operator=(MyList&&) = default;

	MyList(const MyList& other)
		: MyList()
	{
		for (const T& element : other)
		{
			try
			{
				PushBack(element);
			}
			catch (const std::exception&)
			{
				Clear();
				throw;
			}
		}
	}

	MyList& operator=(const MyList& other)
	{
		if (this != &other)
		{
			MyList<T> tmp(other);

			std::swap(m_beginPtr, tmp.m_beginPtr);
			std::swap(m_endPtr, tmp.m_endPtr);
			std::swap(m_length, tmp.m_length);
		}

		return *this;
	}

	~MyList() noexcept
	{
		Clear();
		delete m_beginPtr->prev;
		delete m_endPtr;
	}

	Iterator begin()
	{
		return Iterator(m_beginPtr);
	}

	Iterator end()
	{
		return Iterator(m_endPtr);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_beginPtr);
	}

	ConstIterator end() const
	{
		return ConstIterator(m_endPtr);
	}

	ConstIterator cbegin() const
	{
		return ConstIterator(m_beginPtr);
	}

	ConstIterator cend() const
	{
		return ConstIterator(m_endPtr);
	}

	ReverseIterator rbegin()
	{
		return std::make_reverse_iterator(end());
	}

	ReverseIterator rend()
	{
		return std::make_reverse_iterator(begin());
	}

	ConstReverseIterator rbegin() const
	{
		return std::make_reverse_iterator(end());
	}

	ConstReverseIterator rend() const
	{
		return std::make_reverse_iterator(begin());
	}

	ConstReverseIterator crbegin() const
	{
		return std::make_reverse_iterator(cend());
	}

	ConstReverseIterator crend() const
	{
		return std::make_reverse_iterator(cbegin());
	}

	bool IsEmpty() const
	{
		return !m_length;
	}

	operator bool() const { return !IsEmpty(); }

	size_t GetLength() const
	{
		return m_length;
	}

	MyList& PushBack(const T& data)
	{
		Insert(cend(), data);
		return *this;
	}

	MyList& PushFront(const T& data)
	{
		Insert(cbegin(), data);
		return *this;
	}

	MyList& PopBack()
	{
		Erase(--cend());
		return *this;
	}

	MyList& PopFront()
	{
		Erase(cbegin());
		return *this;
	}

	const T& GetBack() const
	{
		if (IsEmpty())
			throw std::logic_error("List is empty");

		return m_endPtr->prev->data;
	}

	const T& GetFront() const
	{
		if (IsEmpty())
			throw std::logic_error("List is empty");

		return m_beginPtr->data;
	}

	Iterator Insert(const ListBaseIterator<T>& where, const T& data)
	{
		NodePtr<T> newNodePtr = new ListNode<T>(data);
		NodePtr<T> wherePtr = where.m_nodePtr;

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

	Iterator Erase(const ListBaseIterator<T>& where)
	{
		if (IsEmpty())
			throw std::logic_error("List is empty");

		NodePtr<T> wherePtr = where.m_nodePtr;

		if (wherePtr->next == nullptr || wherePtr->prev == nullptr)
			throw std::logic_error("Past-the-last element erase violation");

		NodePtr<T> followingPtr;
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

	void Clear() noexcept
	{
		if (!IsEmpty())
		{
			m_beginPtr->prev->next = m_endPtr;
			m_endPtr->prev = m_beginPtr->prev;

			NodePtr<T> tmp;
			while ((tmp = m_beginPtr) != m_endPtr)
			{
				m_beginPtr = m_beginPtr->next;
				delete tmp;
			}

			m_length = 0;
		}
	}

private:
	NodePtr<T> m_beginPtr = nullptr;
	NodePtr<T> m_endPtr = nullptr;
	size_t m_length = 0;
};
