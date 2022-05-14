#pragma once
#include <iterator>

class MyBaseIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;

	MyBaseIterator();
	MyBaseIterator(char* data);

	const char* data() const;

	bool operator!=(const MyBaseIterator& other) const;
	bool operator==(const MyBaseIterator& other) const;

protected:
	char* m_data;
};
