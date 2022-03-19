#include <catch2/catch.hpp>
#include <lib/html_decode.h>

TEST_CASE("HtmlDecode replaces HTML entity symbols with their normal representation")
{
	REQUIRE(HtmlDecode("Some &quot;text&apos;with&lt;html&gt;") == "Some \"text'with<html>");

	REQUIRE(HtmlDecode("Some &quot;text&apos;with&lt;html&gt;entities") == "Some \"text'with<html>entities");

	REQUIRE(HtmlDecode("&quot;&apos;&amp;&apos;&lt;&amp;&gt;") == "\"'&'<&>");

	REQUIRE(HtmlDecode("&amp;lt;") == "&lt;");
}

TEST_CASE("Invalid HTML entities must be not parsed")
{
	REQUIRE(HtmlDecode("&do;&you;&rly;&wanna;&parse;&that;&quot;") == "&do;&you;&rly;&wanna;&parse;&that;\"");

	REQUIRE(HtmlDecode("&qu; &quot &invalid;") == "&qu; &quot &invalid;");

	REQUIRE(HtmlDecode("&;") == "&;");

	REQUIRE(HtmlDecode("&qu;terrifying &smth;test&again;&lt;") == "&qu;terrifying &smth;test&again;<");
}

TEST_CASE("Text without HTML entities must be not changed")
{
	REQUIRE(HtmlDecode("") == "");

	REQUIRE(HtmlDecode("absolutely no <html>   entities") == "absolutely no <html>   entities");

	REQUIRE(HtmlDecode("live&again") == "live&again");
}