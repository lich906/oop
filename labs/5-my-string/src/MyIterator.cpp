#include "MyIterator.h"

MyIterator::MyIterator()
	: m_data(nullptr)
{
}

MyIterator::MyIterator(pointer data)
	: m_data(data)
{
}

const MyIterator::pointer MyIterator::data() const
{
	return m_data;
}

MyIterator::reference MyIterator::operator*()
{
	return *m_data;
}

const bool MyIterator::operator!=(const MyIterator& other) const
{
	return m_data != other.data();
}

MyIterator& MyIterator::operator++()
{
	m_data += 1;
	return *this;
}

MyIterator MyIterator::operator++(int)
{
	return MyIterator(m_data + 1);
}
