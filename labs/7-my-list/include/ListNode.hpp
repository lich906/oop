#pragma once

template <typename T>
struct ListNode;

template <typename T>
using NodePtr = ListNode<T>*;

template <typename T>
struct ListNode
{
	ListNode() = default;

	ListNode(T data)
		: data(std::move(data))
	{
	}

	T data;
	NodePtr<T> next = nullptr;
	NodePtr<T> prev = nullptr;
};
