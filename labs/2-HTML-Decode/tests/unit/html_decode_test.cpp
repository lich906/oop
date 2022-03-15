#include <catch2/catch.hpp>
#include <lib/html_decode.h>

TEST_CASE("HtmlDecode replaces HTML entity symbols with their normal representation")
{
	REQUIRE(HtmlDecode("Some &quot;text&apos;with&lt;html&gt;") == "Some \"text'with<html>");

	REQUIRE(HtmlDecode("Some &quot;text&apos;with&lt;html&gt;entities") == "Some \"text'with<html>entities");

	REQUIRE(HtmlDecode("&quot;&apos;&amp;&apos;&lt;&amp;&gt;") == "\"'&'<&>");

	//доработать
	SECTION("Invalid html entities must be not parsed")
	{
		REQUIRE(HtmlDecode("&qu;&quot;&quot;&quot;") == "&qu;\"\"\"");
		REQUIRE(HtmlDecode("&qu;&invalid;") == "&qu;&invalid;");
		REQUIRE(HtmlDecode("&;") == "&;");
		REQUIRE(HtmlDecode("&qu;hello &smth;world&again;&lt;") == "&qu;hello &smth;world&again;<");
	}

	REQUIRE(HtmlDecode("") == "");

	REQUIRE(HtmlDecode("no html entities") == "no html entities");

	REQUIRE(HtmlDecode("dead&tnndf") == "dead&tnndf");

	REQUIRE(HtmlDecode("&amp;lt;") == "&lt;");
}