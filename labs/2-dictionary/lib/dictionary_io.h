#pragma once
#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, std::vector<std::string>> Dictionary;
typedef std::pair<std::string, std::vector<std::string>> DictionaryRecord;

Dictionary ReadDictionary(std::istream& in);

bool RewriteDictionary(std::ostream& out, const Dictionary& dict);

DictionaryRecord ParseDictionaryRecord(const std::string& recordString);
