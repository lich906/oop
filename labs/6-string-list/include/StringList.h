#pragma once
#include <stdexcept>
#include <string>

class StringList
{
public:
	StringList() = default;
	StringList(StringList&&) = default;
	StringList(const StringList&) = delete;

	~StringList();

	bool IsEmpty() const;
	operator bool() const { return !IsEmpty(); }

	size_t GetLength() const;

	StringList& PushBack(const std::string& data);
	StringList& PushFront(const std::string& data);

	std::string GetBack() const;
	std::string GetFront() const;

	void Clear();

private:
	struct ListNode
	{
		ListNode(std::string data)
			: data(std::move(data))
		{
		}

		std::string data;
		ListNode* next = nullptr;
		ListNode* prev = nullptr;
	};

	using NodePtr = ListNode*;

	NodePtr m_beginPtr = nullptr;
	NodePtr m_endPtr = nullptr;
	size_t m_length = 0;
};
