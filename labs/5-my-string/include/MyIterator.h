#pragma once
#include <iterator>
class MyIterator;
class MyConstIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = const char;
	using difference_type = ptrdiff_t;
	using pointer = const char*;
	using reference = const char&;

	MyConstIterator();
	MyConstIterator(pointer data);

	pointer data() const;
	pointer operator->() const;

	reference operator*() const;

	bool operator!=(const MyConstIterator& other) const;
	bool operator==(const MyConstIterator& other) const;

	MyConstIterator& operator++();
	MyConstIterator operator++(int);

private:
	pointer m_data;
};

class MyIterator : public MyConstIterator
{
public:
	using value_type = char;
	using pointer = char*;
	using reference = char&;

	MyIterator();
	MyIterator(pointer data);

	const char* data() const;
	pointer operator->() const;
	
	reference operator*() const;

	MyIterator& operator++();
	MyIterator operator++(int);

private:
	pointer m_data;
};
