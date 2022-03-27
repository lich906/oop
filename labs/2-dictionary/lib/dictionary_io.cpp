#include "dictionary_io.h"

#include <iostream>
#include <sstream>

constexpr char TRANSLATION_LIST_DELIM = ':';
constexpr char TRANSLATION_VARIANTS_DELIM = ',';

DictionaryRecord ParseDictionaryRecord(const std::string& recordString)
{
	std::stringstream ss(recordString);
	std::string word;
	std::string translationWord;
	std::vector<std::string> translationVariants;
	
	std::getline(ss, word, TRANSLATION_LIST_DELIM);
	while (std::getline(ss, translationWord, TRANSLATION_VARIANTS_DELIM))
	{
		translationVariants.push_back(translationWord);
	}

	return std::make_pair(word, translationVariants);
}

Dictionary ReadDictionary(std::istream& in)
{
	Dictionary dict;
	DictionaryRecord dictRecord;
	std::string dictRecordString;

	while (std::getline(in, dictRecordString))
	{
		if (!dictRecordString.empty())
		{
			dictRecord = ParseDictionaryRecord(dictRecordString);
			dict[std::get<0>(dictRecord)] = std::get<1>(dictRecord);
		}
	}

	return dict;
}

bool RewriteDictionary(std::ostream& out, const Dictionary& dict)
{
	for (const auto& [word, translationVariants] : dict)
	{
		out << word << TRANSLATION_LIST_DELIM;
		if (!out)
			return false;
		for (const std::string& translate : translationVariants)
		{
			out << translate << TRANSLATION_VARIANTS_DELIM;
			if (!out)
				return false;
		}
		out << std::endl;
	}

	return true;
}