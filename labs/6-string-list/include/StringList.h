#pragma once
#include <string>

class StringList
{
public:
	bool IsEmpty() const;

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
