#pragma once
#include <vector>
#include <iostream>
#include <optional>

std::optional<std::vector<float>> ReadVectorOfNumbers(std::istream& in);

bool PrintVector(std::ostream& out, const std::vector<float>& vect);

std::optional<std::vector<float>> ProcessVect(std::vector<float> vect);
