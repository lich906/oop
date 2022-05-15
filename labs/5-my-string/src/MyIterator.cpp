#include "MyIterator.h"

MyBaseIterator::MyBaseIterator()
	: m_data(nullptr)
{
}

MyBaseIterator::MyBaseIterator(char* data)
	: m_data(data)
{
}

const char* MyBaseIterator::data() const
{
	return m_data;
}

bool MyBaseIterator::operator!=(const MyBaseIterator& other) const
{
	return m_data != other.m_data;
}

bool MyBaseIterator::operator==(const MyBaseIterator& other) const
{
	return !(*this != other);
}

bool MyBaseIterator::operator<(const MyBaseIterator& other) const
{
	return other - *this > 0;
}

bool MyBaseIterator::operator>(const MyBaseIterator& other) const
{
	return *this - other > 0;
}

bool MyBaseIterator::operator>=(const MyBaseIterator& other) const
{
	return !(*this < other);
}

bool MyBaseIterator::operator<=(const MyBaseIterator& other) const
{
	return !(*this > other);
}

MyConstIterator::MyConstIterator()
	: MyBaseIterator()
{
}

MyConstIterator::MyConstIterator(char* data)
	: MyBaseIterator(data)
{
}

MyConstIterator::MyConstIterator(const MyIterator& it)
	: MyBaseIterator(it)
{
}

MyConstIterator::pointer MyConstIterator::operator->() const
{
	return m_data;
}

const MyConstIterator::reference MyConstIterator::operator*() const
{
	return *m_data;
}

MyConstIterator& MyConstIterator::operator++()
{
	++m_data;
	return *this;
}

MyConstIterator MyConstIterator::operator++(int)
{
	MyConstIterator tmp = MyConstIterator(m_data);
	++m_data;
	return tmp;
}

MyConstIterator& MyConstIterator::operator--()
{
	--m_data;
	return *this;
}

MyConstIterator MyConstIterator::operator--(int)
{
	MyConstIterator tmp = MyConstIterator(m_data);
	--m_data;
	return tmp;
}

MyConstIterator& MyConstIterator::operator+=(difference_type diff)
{
	m_data += diff;
	return *this;
}

MyConstIterator MyConstIterator::operator+(difference_type diff) const
{
	MyConstIterator tmp = *this;
	return tmp += diff;
}

MyConstIterator& MyConstIterator::operator-=(difference_type diff)
{
	m_data -= diff;
	return *this;
}

MyConstIterator MyConstIterator::operator-(difference_type diff) const
{
	MyConstIterator tmp = *this;
	return tmp -= diff;
}

MyConstIterator::reference MyConstIterator::operator[](difference_type diff) const
{
	return *(*this + diff);
}

MyIterator::MyIterator()
	: MyBaseIterator()
{
}

MyIterator::MyIterator(pointer data)
	: MyBaseIterator(data)
{
}

MyIterator::pointer MyIterator::operator->() const
{
	return m_data;
}

MyIterator::reference MyIterator::operator*() const
{
	return *m_data;
}

MyIterator& MyIterator::operator++()
{
	++m_data;
	return *this;
}

MyIterator MyIterator::operator++(int)
{
	MyIterator tmp = MyIterator(m_data);
	++m_data;
	return tmp;
}

MyIterator& MyIterator::operator--()
{
	--m_data;
	return *this;
}

MyIterator MyIterator::operator--(int)
{
	MyIterator tmp = MyIterator(m_data);
	--m_data;
	return tmp;
}

MyIterator& MyIterator::operator+=(difference_type diff)
{
	m_data += diff;
	return *this;
}

MyIterator MyIterator::operator+(difference_type diff) const
{
	MyIterator tmp = *this;
	return tmp += diff;
}

MyIterator& MyIterator::operator-=(difference_type diff)
{
	m_data -= diff;
	return *this;
}

MyIterator MyIterator::operator-(difference_type diff) const
{
	MyIterator tmp = *this;
	return tmp -= diff;
}

MyIterator::reference MyIterator::operator[](difference_type diff) const
{
	return *(*this + diff);
}

MyBaseIterator::difference_type operator-(const MyBaseIterator& lhs, const MyBaseIterator& rhs)
{
	return lhs.m_data - rhs.m_data;
}

MyIterator operator+(MyBaseIterator::difference_type diff, const MyIterator& iterator)
{
	return iterator + diff;
}

MyConstIterator operator+(MyBaseIterator::difference_type diff, const MyConstIterator& iterator)
{
	return iterator + diff;
}
