#include <catch2/catch.hpp>
#include "HttpUrl.h"

TEST_CASE("Initialize url specifying all components")
{
	SECTION("Document string does not start with '/', port is default")
	{
		HttpUrl url("www.useful-site.com", "site/index.php", HttpUrl::Protocol::HTTP, 80);

		REQUIRE(url.GetDomain() == "www.useful-site.com");
		REQUIRE(url.GetDocument() == "/site/index.php");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(url.GetPort() == 80);
		REQUIRE(url.GetURL() == "http://www.useful-site.com/site/index.php");
	}

	SECTION("Document string starts with '/', port is default")
	{
		HttpUrl url("www.github.com", "/lich906/oop.git", HttpUrl::Protocol::HTTPS, 443);

		REQUIRE(url.GetDomain() == "www.github.com");
		REQUIRE(url.GetDocument() == "/lich906/oop.git");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetPort() == 443);
		REQUIRE(url.GetURL() == "https://www.github.com/lich906/oop.git");
	}

	SECTION("Specify non-default port")
	{
		HttpUrl url("www.darkside.ru", "/news/index.html", HttpUrl::Protocol::HTTPS, 6112);

		REQUIRE(url.GetDomain() == "www.darkside.ru");
		REQUIRE(url.GetDocument() == "/news/index.html");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetPort() == 6112);
		REQUIRE(url.GetURL() == "https://www.darkside.ru:6112/news/index.html");
	}
}

TEST_CASE("Initialize url without specifying port and/or protocol")
{
	SECTION("Port is not specified, expect default port is set")
	{
		HttpUrl url("liquipedia.net", "/warcraft", HttpUrl::Protocol::HTTPS);

		REQUIRE(url.GetDomain() == "liquipedia.net");
		REQUIRE(url.GetDocument() == "/warcraft");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetPort() == 443);
		REQUIRE(url.GetURL() == "https://liquipedia.net/warcraft");
	}

	SECTION("Port and protocol not specified")
	{
		HttpUrl url("habr.com", "/ru/company/selectel/blog/653749/");

		REQUIRE(url.GetDomain() == "habr.com");
		REQUIRE(url.GetDocument() == "/ru/company/selectel/blog/653749/");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(url.GetPort() == 80);
		REQUIRE(url.GetURL() == "http://habr.com/ru/company/selectel/blog/653749/");
	}
}

TEST_CASE("Initialize with valid url string")
{
	SECTION("Valid url")
	{
		HttpUrl url("https://www.youtube.com/watch?v=a59-SIDh0so");

		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "/watch?v=a59-SIDh0so");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetPort() == 443);
		REQUIRE(url.GetURL() == "https://www.youtube.com/watch?v=a59-SIDh0so");
	}

	SECTION("Valid url: should use default port")
	{
		HttpUrl url("https://www.youtube.com:/watch?v=a59-SIDh0so");

		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "/watch?v=a59-SIDh0so");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetPort() == 443);
		REQUIRE(url.GetURL() == "https://www.youtube.com/watch?v=a59-SIDh0so");
	}

	SECTION("Valid url: max port value 65535")
	{
		HttpUrl url("https://www.youtube.com:65535/watch?v=a59-SIDh0so");

		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "/watch?v=a59-SIDh0so");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTPS);
		REQUIRE(url.GetPort() == 65535);
		REQUIRE(url.GetURL() == "https://www.youtube.com:65535/watch?v=a59-SIDh0so");
	}

	SECTION("Valid url with port")
	{
		HttpUrl url("http://www.youtube.com:999/watch?v=lx0L9htLDA0");

		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "/watch?v=lx0L9htLDA0");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(url.GetPort() == 999);
		REQUIRE(url.GetURL() == "http://www.youtube.com:999/watch?v=lx0L9htLDA0");
	}

	SECTION("Valid url with port and without document")
	{
		HttpUrl url("http://www.youtube.com:1337");

		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "/");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(url.GetPort() == 1337);
		REQUIRE(url.GetURL() == "http://www.youtube.com:1337/");
	}

	SECTION("Valid url with port and without document")
	{
		HttpUrl url("http://www.youtube.com");

		REQUIRE(url.GetDomain() == "www.youtube.com");
		REQUIRE(url.GetDocument() == "/");
		REQUIRE(url.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(url.GetPort() == 80);
		REQUIRE(url.GetURL() == "http://www.youtube.com/");
	}
}

TEST_CASE("Try initialize with invalid url string")
{
	SECTION("Invalid protocol")
	{
		REQUIRE_THROWS_WITH(HttpUrl("hts://www.youtube.com/watch?v=uAwIBtov5EM"), "Invalid protocol");
		REQUIRE_THROWS_WITH(HttpUrl("://www.youtube.com/watch?v=uAwIBtov5EM"), "Invalid protocol");
		REQUIRE_THROWS_WITH(HttpUrl("www.youtube.com/watch?v=uAwIBtov5EM"), "Invalid protocol");
	}

	SECTION("Invalid domain")
	{
		REQUIRE_THROWS_WITH(HttpUrl("https://youtube/watch?v=uAwIBtov5EM"), "Invalid domain");
		REQUIRE_THROWS_WITH(HttpUrl("https://youtube.345/watch?v=uAwIBtov5EM"), "Invalid domain");
		REQUIRE_THROWS_WITH(HttpUrl("https://youtubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutubeyoutube.com/watch?v=uAwIBtov5EM"), "Invalid domain");
	}

	SECTION("Invalid port")
	{
		REQUIRE_THROWS_WITH(HttpUrl("https://www.youtube.com:334955/watch?v=uAwIBtov5EM"), "Invalid port");
		REQUIRE_THROWS_WITH(HttpUrl("https://www.youtube.com:65536/watch?v=uAwIBtov5EM"), "Invalid port");
	}

	SECTION("Invalid document")
	{
		REQUIRE_THROWS_WITH(HttpUrl("https://www.youtube.com/watc^$&#@($)Btov5EM"), "Invalid document path");
	}
}
