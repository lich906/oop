#include <algorithm>
#include <vector>

template<typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	auto maxElementIterator = std::max_element(arr.begin(), arr.end(), less);

	if (maxElementIterator != arr.end())
	{
		maxValue = *maxElementIterator;
		return true;
	}

	return false;
}
