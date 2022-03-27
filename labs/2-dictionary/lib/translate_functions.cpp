#include "translate_functions.h"

#include <iostream>
#include <algorithm>

const std::string EXIT_PHRASE = "...";

bool AskForUpdatingDictionaryFile();
bool IsEnLanguage(const std::string& word);
bool IsRuLanguage(const std::string& word);

Operation PerformOperationByUserInput(const std::string& userInput, bool dictWasModified)
{
	if (userInput == EXIT_PHRASE)
	{
		if (dictWasModified && AskForUpdatingDictionaryFile())
		{
			return Operation::ExitAndSaveChanges;
		}
		else
		{
			return Operation::ExitAndDiscardChanges;
		}
	}

	if (IsEnLanguage(userInput))
	{
		return Operation::TranslateFromEn;
	}

	if (IsRuLanguage(userInput))
	{
		return Operation::TranslateFromRu;
	}

	return Operation::BadInput;
}

bool AskForUpdatingDictionaryFile()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
	char usrAnswer = std::cin.get();
	if (usrAnswer == 'Y' || usrAnswer == 'y')
	{
		return true;
	}

	return false;
}

bool IsEnLanguage(const std::string& word)
{
	if ((word[0] >= 'A' && word[0] <= 'Z') || (word[0] >= 'a' && word[0] <= 'z'))
	{
		return true;
	}

	return false;
}

bool IsRuLanguage(const std::string& word)
{
	if ((word[0] >= 'А' && word[0] <= 'я'))
	{
		return true;
	}

	return false;
}

std::optional<std::vector<std::string>> GetEnWordTranslations(const std::string& word, const Dictionary& dict)
{
	if (!dict.contains(word))
	{
		return std::nullopt;
	}

	return dict.at(word);
}

void AddNewEnWord(Dictionary& dict, const std::string& word, const std::string& translation)
{
	dict[word] = std::vector<std::string>{ translation };
}

void AddNewRuWord(Dictionary& dict, const std::string& word, const std::string& translation)
{
	if (dict.contains(translation))
	{
		dict[translation].push_back(word);
	}
	else
	{
		dict[translation] = std::vector<std::string>{ word };
	}
}

std::optional<std::vector<std::string>> GetRuWordTranslations(const std::string& word, const Dictionary& dict)
{
	std::vector<std::string> translations;

	for (const auto& [enWord, ruTranslations] : dict)
	{
		if (std::find(ruTranslations.begin(), ruTranslations.end(), word) != ruTranslations.end())
		{
			translations.push_back(enWord);
		}
	}

	if (translations.empty())
	{
		return std::nullopt;
	}

	return translations;
}

void PrintTranslations(std::ostream& out, const std::vector<std::string>& translations)
{
	bool first = true;
	for (std::string word : translations)
	{
		if (!first)
		{
			out << ", ";
		}
		else
		{
			first = false;
		}

		out << word;
	}

	out << std::endl;
}