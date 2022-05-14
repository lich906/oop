#pragma once
#include "MyBaseIterator.h"

class MyIterator : public MyBaseIterator
{
public:
	using value_type = char;
	using pointer = char*;
	using reference = char&;

	MyIterator();
	MyIterator(pointer data);

	pointer operator->() const;
	
	reference operator*() const;

	MyIterator& operator++();
	MyIterator operator++(int);

	MyIterator& operator--();
	MyIterator operator--(int);
};

class MyConstIterator : public MyBaseIterator
{
public:
	using value_type = const char;
	using pointer = const char*;
	using reference = const char&;

	MyConstIterator();
	MyConstIterator(char* data);
	MyConstIterator(const MyIterator& it);

	pointer operator->() const;

	reference operator*() const;

	MyConstIterator& operator++();
	MyConstIterator operator++(int);

	MyConstIterator& operator--();
	MyConstIterator operator--(int);
};
