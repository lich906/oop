#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>

void LogError(const std::string& msg)
{
	std::cout << msg;
}

void InsertSort(std::vector<float>& vect, const float& val)
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
		LogError("Failed to read data.\n");
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
			LogError("Failed to print out data.\n");
			return false;
		}
	}

	out << '\n';

	return true;
}

int main()
{
	auto optVect = ReadVectorOfNumbers(std::cin);

	if (!optVect.has_value())
	{
		return 1;
	}

	std::vector<float> vect = optVect.value();
	const auto [min, max] = std::minmax_element(vect.begin(), vect.end());

	float val = *max / *min;

	std::for_each(vect.begin(), vect.end(), [=](float& elt) { elt *= val; });

	if (!PrintVector(std::cout, vect))
	{
		return 1;
	}

	return 0;
}
