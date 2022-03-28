#pragma once
#include "dictionary_io.h"

#include <optional>

enum class Operation
{
	Exit,
	Translate
};

Operation GetOperationByUserInput(const std::string& userInput);

std::optional<std::vector<std::string>> GetTranslations(const std::string& word, const Dictionary& dict);

void AddNewWord(Dictionary& dict, const std::string& word, const std::string& translation);

void PrintTranslations(std::ostream& out, const std::vector<std::string>& translations);

bool PerformTranslation(Dictionary& dict, const std::string& word);

bool AskForUpdatingDictionaryFile();

std::string GetUserInput();
