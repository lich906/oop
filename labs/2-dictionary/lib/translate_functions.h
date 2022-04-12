// TODO: переименовать модуль -> translate
#pragma once
#include "dictionary_io.h"

#include <optional>

enum class Operation
{
	Exit,
	Translate
};

// TODO: переместить в другой модуль
Operation GetOperationByUserInput(const std::string& userInput);

std::optional<std::vector<std::string>> GetTranslations(const std::string& word, const Dictionary& dict);

void AddNewWord(Dictionary& dict, const std::string& word, const std::string& translation);

void PrintTranslations(std::ostream& out, const std::vector<std::string>& translations);

bool PerformTranslation(Dictionary& dict, const std::string& word);

// TODO: переместить в другой модуль
bool AskForUpdatingDictionaryFile();

// TODO: переместить в другой модуль
std::string GetUserInput();
