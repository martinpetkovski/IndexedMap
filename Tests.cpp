#include "IndexedMap.h"

#define CATCH_CONFIG_MAIN
#include "Catch.hpp"

#include <iostream>
#include <string>

TEST_CASE("Operations", "[operations]") 
{
	IndexedMap<std::string, int> im;

	REQUIRE(im.insert("PositionX", 12));
	REQUIRE(im.insert("PositionY", 1));

	REQUIRE(im["PositionX"] == 12);
	REQUIRE(im["PositionY"] == 1);

	im["PositionX"] = 72;

	REQUIRE(im["PositionX"] == 72);
	REQUIRE(im.get_index(0) == 72);

	REQUIRE(im.size() == 2);

	im.insert_or_assign("PositionZ", 42);
	REQUIRE(im["PositionZ"] == 42);

	im.insert_or_assign("PositionZ", 69);
	REQUIRE(im["PositionZ"] == 69);

	im.remove("PositionY");
	REQUIRE(im.size() == 2);
	REQUIRE_FALSE(im.is_index_valid(3));
	REQUIRE_FALSE(im.exists("PositionY"));
	REQUIRE(im.exists("PositionZ"));
	REQUIRE(im["PositionZ"] == 69);

	int iterationSum = 0;
	for (const int p : im)
	{
		iterationSum += p;
	}

	REQUIRE(iterationSum == 141);

	im.clear();
	REQUIRE(im.is_empty());
}