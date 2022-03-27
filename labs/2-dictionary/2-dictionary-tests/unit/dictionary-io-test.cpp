#include <catch2/catch.hpp>
#include <lib/dictionary_io.h>

#include <sstream>

TEST_CASE("ParseDictionaryRecord returns pair(word, translations) from string with format <word>:<translations>\
where <translations> = <translation1>,<translation2>,...")
{
	SECTION("word with translations")
	{
		std::string str("cat:кошка,кот,кошак,кiт");
		DictionaryRecord rec = ParseDictionaryRecord(str);
		REQUIRE(std::get<0>(rec) == "cat");
		REQUIRE_THAT(std::get<1>(rec), Catch::Matchers::Equals(std::vector<std::string>{ "кошка", "кот", "кошак", "кiт" }));
	}

	SECTION("no translations")
	{
		std::string str("cat:");
		DictionaryRecord rec = ParseDictionaryRecord(str);
		REQUIRE(std::get<0>(rec) == "cat");
		REQUIRE_THAT(std::get<1>(rec), Catch::Matchers::Equals(std::vector<std::string>{}));
	}
}