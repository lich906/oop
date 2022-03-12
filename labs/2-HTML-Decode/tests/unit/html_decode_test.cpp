#include <catch2/catch.hpp>
#include <lib/html_decode.h>

TEST_CASE("HtmlDecode replaces HTML entity symbols with their normal representation")
{
	REQUIRE(HtmlDecode("Some &quot;text&apos;with&lt;html&gt;entities") == "Some \"text'with<html>entities");

	REQUIRE(HtmlDecode("Some &quot;text&apos;with&lt;html&gt;") == "Some \"text'with<html>");

	REQUIRE(HtmlDecode("&quot;&apos;&amp;&apos;&lt;&amp;&gt;") == "\"'&'<&>");

	REQUIRE(HtmlDecode("&quot;&quot;&quot;&quot;") == "\"\"\"\"");

	SECTION("Invalid html entities replaces with empty string")
	{
		REQUIRE(HtmlDecode("&qu;&quot;&quot;&quot;") == "\"\"\"");
		REQUIRE(HtmlDecode("&qu;&invalid;") == "");
		REQUIRE(HtmlDecode("&;") == "");
		REQUIRE(HtmlDecode("&qu;hello &smth;world&again;&lt;") == "hello world<");
	}

	REQUIRE(HtmlDecode("") == "");

	REQUIRE(HtmlDecode("no html entities") == "no html entities");
}