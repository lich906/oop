#include "MyBaseIterator.h"

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
