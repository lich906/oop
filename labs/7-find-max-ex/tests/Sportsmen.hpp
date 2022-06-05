#pragma once
#include <string>

class Sportsmen
{
public:
	Sportsmen() = default;

	Sportsmen(std::string name, short height, short weight)
		: m_name(name)
		, m_height(height)
		, m_weight(weight)
	{
	}

	const std::string& GetName() const { return m_name; }

	short GetHeight() const { return m_height; }

	short GetWeight() const { return m_weight; }

private:
	std::string m_name;
	short m_height;
	short m_weight;
};