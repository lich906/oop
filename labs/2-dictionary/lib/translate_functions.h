#pragma once
#include "dictionary_io.h"

#include <optional>

enum class Operation
{
	ExitAndDiscardChanges,
	ExitAndSaveChanges,
	TranslateFromEn,
	TranslateFromRu,
	BadInput
};

Operation PerformOperationByUserInput(const std::string& userInput, bool dictWasModified);

std::optional<std::vector<std::string>> GetEnWordTranslations(const std::string& word, const Dictionary& dict);

std::optional<std::vector<std::string>> GetRuWordTranslations(const std::string& word, const Dictionary& dict);

void AddNewEnWord(Dictionary& dict, const std::string& word, const std::string& translation);

void AddNewRuWord(Dictionary& dict, const std::string& word, const std::string& translation);

void PrintTranslations(std::ostream& out, const std::vector<std::string>& translations);
