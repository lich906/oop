#include <algorithm>

#include "vector_functions.h"

void InsertSort(std::vector<float>& vect, float val)
{
	for (size_t pos = 0; pos < vect.size(); ++pos)
	{
		if (vect[pos] > val)
		{
			vect.insert(vect.begin() + pos, val);
			return;
		}
	}

	vect.push_back(val);
}

std::optional<std::vector<float>> ReadVectorOfNumbers(std::istream& in)
{
	std::vector<float> vect;
	float num;

	while (in >> num)
	{
		InsertSort(vect, num);
	}

	if (in.bad() || vect.empty())
	{
		return std::nullopt;
	}

	return vect;
}

bool PrintVector(std::ostream& out, const std::vector<float>& vect)
{
	for (float elt : vect)
	{
		if (!(out << elt << ' '))
		{
			return false;
		}
	}

	out << '\n';

	return true;
}

std::optional<std::vector<float>> ProcessVect(std::vector<float> vect)
{
	if (vect.empty())
	{
		return std::nullopt;
	}

	const auto [min, max] = std::minmax_element(vect.begin(), vect.end());

	//неопределенное поведение при пустом векторе
	if (*min == 0)
	{
		return std::nullopt;
	}

	//подобрать имя
	float maxminQuotient = *max / *min;

	auto processElement = [&](const float& elt) -> float {
		return elt * maxminQuotient;
	};

	std::transform(vect.begin(), vect.end(), vect.begin(), processElement);

	if (maxminQuotient < 0)
	{
		std::reverse(vect.begin(), vect.end());
	}

	return vect;
}
