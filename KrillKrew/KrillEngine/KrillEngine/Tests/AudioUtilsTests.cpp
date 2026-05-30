#include "catch_amalgamated.hpp"
#include "../AudioUtils.h"

TEST_CASE("Volume below minimum clamps to zero", "[Audio][TDD]")
{
	REQUIRE(ClampVolume(-10) == 0);
}

TEST_CASE("Volume within range is unchanged", "[Audio][TDD]")
{
	REQUIRE(ClampVolume(64) == 64);
}

TEST_CASE("Volume above maximum clamps to 128", "[Audio][TDD]")
{
	REQUIRE(ClampVolume(200) == 128);
}

TEST_CASE("Volume at minimum remains zero", "[Audio][TDD]")
{
	REQUIRE(ClampVolume(0) == 0);
}

TEST_CASE("Volume at maximum remains 128", "[Audio][TDD]")
{
	REQUIRE(ClampVolume(128) == 128);
}