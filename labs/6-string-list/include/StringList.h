#pragma once
#include <stdexcept>
#include <string>

class StringList
{
public:
	StringList() = default;
	StringList(StringList&&) = default;
	StringList(const StringList&) = delete;

	~StringList() noexcept;

	bool IsEmpty() const;
	operator bool() const { return !IsEmpty(); }

	size_t GetLength() const;

	StringList& PushBack(const std::string& data);
	StringList& PushFront(const std::string& data);

	StringList& PopBack();
	StringList& PopFront();

	std::string GetBack() const;
	std::string GetFront() const;

	void Clear() noexcept;

private:
	struct ListNode;
	using NodePtr = ListNode*;

	struct ListNode
	{
		ListNode(std::string data)
			: data(std::move(data))
		{
		}

		std::string data;
		NodePtr next = nullptr;
		NodePtr prev = nullptr;
	};

	NodePtr m_beginPtr = nullptr;
	NodePtr m_endPtr = nullptr;
	size_t m_length = 0;
};
