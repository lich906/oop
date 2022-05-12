#pragma once
#include <iterator>

class MyIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = char;
	using difference_type = size_t;
	using pointer = char*;
	using reference = char&;

	MyIterator();
	MyIterator(pointer data);

	const pointer data() const;

	reference operator*();

	const bool operator!=(const MyIterator& other) const;

	MyIterator& operator++();

	MyIterator operator++(int);

private:
	pointer m_data;
};