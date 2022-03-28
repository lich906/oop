#include <iostream>
#include <cstdlib>
#include <cctype>
#include <Windows.h>

#include "lib/translate_functions.h"
#include "lib/file_stream_utils.h"

constexpr auto ARGS_COUNT = 2;

std::optional<std::string> ParseDictFileNameArg(int argc, char* argv[]);

void SaveChanges(std::fstream& dictFile, const std::string& dictFileName, Dictionary& dictionary);

void PerformActionByOperation(const Operation& operation, bool& dictWasModified, Dictionary& dictionary, const std::string& userInput, std::fstream& dictFile, const std::string& dictFileName);

//разбить main()
//поправить кодировку исходников
int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto arg = ParseDictFileNameArg(argc, argv);
	if (!arg.has_value())
	{
		std::cout << "Неверные параметры командной строки. Пример: 2-dictionary.exe <путь до файла со словарем>" << std::endl;
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
	std::string userInput;

	do
	{
		userInput = GetUserInput();
		operation = GetOperationByUserInput(userInput);
		PerformActionByOperation(operation, dictWasModified, dictionary, userInput, dictFile, dictFileName);
	} while (operation != Operation::Exit);

	std::cout << "До свидания." << std::endl;

	return 0;
}

void PerformActionByOperation(const Operation& operation, bool& dictWasModified, Dictionary& dictionary, const std::string& userInput, std::fstream& dictFile, const std::string& dictFileName)
{
	switch (operation)
	{
	case Operation::Translate:
		dictWasModified = PerformTranslation(dictionary, userInput) || dictWasModified;
		break;
	case Operation::Exit:
		if (dictWasModified && AskForUpdatingDictionaryFile())
		{
			SaveChanges(dictFile, dictFileName, dictionary);
		}
		else
		{
			std::cout << "Словарь не был изменен. ";
		}
		break;
	default:
		break;
	}
}

void SaveChanges(std::fstream& dictFile, const std::string& dictFileName, Dictionary& dictionary)
{
	if (!OpenFileStream(dictFile, dictFileName, std::ios::out) || !RewriteDictionary(dictFile, dictionary))
	{
		std::cout << "Не удалось сохранить изменения в словарь. " << std::endl;
	}
	else
	{
		std::cout << "Изменения сохранены. ";
	}
}

std::optional<std::string> ParseDictFileNameArg(int argc, char* argv[])
{
	if (argc != ARGS_COUNT)
	{
		return std::nullopt;
	}

	return std::string(argv[1]);
}
