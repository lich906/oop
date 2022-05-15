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
