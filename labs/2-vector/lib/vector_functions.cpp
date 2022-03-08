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

std::optional<std::vector<float>> ProcessVect(const std::vector<float>& vect)
{
	const auto [min, max] = std::minmax_element(vect.begin(), vect.end());

	if (*min == 0)
	{
		return std::nullopt;
	}

	float val = *max / *min;

	std::vector<float> res;

	auto processElement = [&](float elt) {
		elt *= val;
		res.push_back(elt);
	};

	std::for_each(vect.begin(), vect.end(), processElement);

	if (val < 0)
	{
		std::reverse(res.begin(), res.end());
	}

	return res;
}
