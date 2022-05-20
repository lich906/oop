#pragma once
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound);

void PrintSet(std::ostream& out, const std::set<int>& set, const char* delimiter = ", ");