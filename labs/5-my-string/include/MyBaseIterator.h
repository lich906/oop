#pragma once
#include <iterator>

class MyBaseIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;

	const char* data() const;

	bool operator!=(const MyBaseIterator& other) const;
	bool operator==(const MyBaseIterator& other) const;

protected:
	MyBaseIterator();
	MyBaseIterator(char* data);

	char* m_data;
};
