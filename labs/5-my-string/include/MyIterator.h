#pragma once
#include <iterator>

class MyBaseIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = ptrdiff_t;

	const char* data() const;

	bool operator!=(const MyBaseIterator& other) const;
	bool operator==(const MyBaseIterator& other) const;

	friend MyBaseIterator::difference_type operator-(const MyBaseIterator& lhs, const MyBaseIterator& rhs);

	bool operator<(const MyBaseIterator& other) const;
	bool operator>(const MyBaseIterator& other) const;
	bool operator>=(const MyBaseIterator& other) const;
	bool operator<=(const MyBaseIterator& other) const;

protected:
	MyBaseIterator();
	MyBaseIterator(char* data);

	char* m_data;
};

MyBaseIterator::difference_type operator-(const MyBaseIterator& lhs, const MyBaseIterator& rhs);

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

	MyIterator& operator+=(difference_type diff);
	MyIterator operator+(difference_type diff) const;
	friend MyIterator operator+(difference_type diff, const MyIterator& iterator);

	MyIterator& operator-=(difference_type diff);
	MyIterator operator-(difference_type diff) const;

	reference operator[](difference_type diff) const;
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

	MyConstIterator& operator+=(difference_type diff);
	MyConstIterator operator+(difference_type diff) const;
	friend MyConstIterator operator+(difference_type diff, const MyConstIterator& iterator);

	MyConstIterator& operator-=(difference_type diff);
	MyConstIterator operator-(difference_type diff) const;

	reference operator[](difference_type diff) const;
};
