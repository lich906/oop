#include <iostream>

#include "lib/translate_functions.h"
#include "lib/file_stream_utils.h"

constexpr auto ARGS_COUNT = 2;
constexpr auto USER_INPUT_PREFIX = '>';

std::optional<std::string> ParseDictFileNameArg(int argc, char* argv[]);
std::string GetUserInput();

int main(int argc, char* argv[])
{
	auto arg = ParseDictFileNameArg(argc, argv);
	if (!arg.has_value())
	{
		std::cout << "Неверные аргументы командной строки. Пример: 2-dictionary.exe <путь до файла словаря>" << std::endl;
		return 1;
	}

	std::string dictFileName = arg.value();
	std::fstream dictFile;
	if (!OpenFileStream(dictFile, dictFileName, std::ios::in))
	{
		std::cout << "Не удалось открыть файл словаря. Убедитесь, что файл существует и доступен для чтения." << std::endl;
		return 1;
	}

	Dictionary dictionary = ReadDictionary(dictFile);
	bool dictWasModified = false;
	Operation operation;
	std::string userInput, userTranslation;
	std::optional<std::vector<std::string>> translations;

	do
	{
		userInput = GetUserInput();
		operation = PerformOperationByUserInput(userInput, dictWasModified);

		switch (operation)
		{
		case Operation::TranslateFromEn:
		case Operation::TranslateFromRu:
			(operation == Operation::TranslateFromRu) ? 
				translations = GetRuWordTranslations(userInput, dictionary) : 
				translations = GetEnWordTranslations(userInput, dictionary);
			if (!translations.has_value())
			{
				std::cout << "Не найден перевод для слова \"" << userInput << "\" введите перевод или пустую строку для отказа." << std::endl;
				userTranslation = GetUserInput();
				if (!userTranslation.empty())
				{
					(operation == Operation::TranslateFromRu) ? 
						AddNewRuWord(dictionary, userInput, userTranslation) : 
						AddNewEnWord(dictionary, userInput, userTranslation);
					std::cout << "Слово \"" << userInput << "\" сохранено в словаре как \"" << userTranslation << "\"." << std::endl;
					dictWasModified = true;
				}
				else
				{
					std::cout << "Слово \"" << userInput << "\" проигнорировано." << std::endl;
				}
			}
			else
			{
				PrintTranslations(std::cout, translations.value());
			}
			break;
		case Operation::ExitAndSaveChanges:
			if (!OpenFileStream(dictFile, dictFileName, std::ios::out) || !RewriteDictionary(dictFile, dictionary))
			{
				std::cout << "Не удалось сохранить изменения в файл словаря." << std::endl;
			}
			else
			{
				std::cout << "Изменения сохранены. ";
			}
			break;
		case Operation::ExitAndDiscardChanges:
			std::cout << "Изменения не были внесены в словарь. ";
			break;
		case Operation::BadInput:
			std::cout << "Введено некорректное слово. Попробуйте снова..." << std::endl;
			break;
		default:
			break;
		}

	} while (operation != Operation::ExitAndSaveChanges && operation != Operation::ExitAndDiscardChanges);

	std::cout << "До свидания." << std::endl;

	return 0;
}

std::optional<std::string> ParseDictFileNameArg(int argc, char* argv[])
{
	if (argc != ARGS_COUNT)
	{
		return std::nullopt;
	}

	return std::string(argv[1]);
}

std::string GetUserInput()
{
	std::string userInput;
	std::cout << USER_INPUT_PREFIX;
	std::getline(std::cin, userInput);

	return userInput;
}
