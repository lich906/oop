#include <vector>
#include <iostream>
#include <optional>

void InsertSort(std::vector<float>& vect, const float& val);

std::optional<std::vector<float>> ReadVectorOfNumbers(std::istream& in);

bool PrintVector(std::ostream& out, const std::vector<float>& vect);

std::vector<float> ProcessVect(const std::vector<float>& vect);
