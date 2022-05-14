#include "MyIterator.h"

MyConstIterator::MyConstIterator()
	: m_data(nullptr)
{
}

MyConstIterator::MyConstIterator(pointer data)
	: m_data(data)
{
}

MyConstIterator::pointer MyConstIterator::data() const
{
	return m_data;
}

MyConstIterator::pointer MyConstIterator::operator->() const
{
	return m_data;
}

const MyConstIterator::reference MyConstIterator::operator*() const
{
	return *m_data;
}

bool MyConstIterator::operator!=(const MyConstIterator& other) const
{
	return m_data != other.data();
}

bool MyConstIterator::operator==(const MyConstIterator& other) const
{
	return !(*this != other);
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

MyIterator::MyIterator()
	: m_data(nullptr)
{
}

MyIterator::MyIterator(pointer data)
	: m_data(data)
{
}

const char* MyIterator::data() const
{
	return m_data;
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
