#include "catch_amalgamated.hpp"
#include "../ProjectileObject.h"

TEST_CASE("Projectile lifetime cannot be negative", "[Projectile][TDD]")
{
	ProjectileObject projectile;

	projectile.SetLifeTime(-5.0f);

	REQUIRE(projectile.GetLifetime() == Catch::Approx(0.0f));
}

TEST_CASE("Projectile lifetime accepts positive value", "[Projectile][TDD]")
{
	ProjectileObject projectile;

	projectile.SetLifeTime(3.0f);

	REQUIRE(projectile.GetLifetime() == Catch::Approx(3.0f));
}

TEST_CASE("Projectile lifetime reduces but does not go below zero", "[Projectile][TDD]")
{
	ProjectileObject projectile;

	projectile.SetLifeTime(1.0f);
	projectile.ReduceLifeTime(2.0f);

	REQUIRE(projectile.GetLifetime() == Catch::Approx(0.0f));
}

TEST_CASE("Projectile lifetime is not reduced by negative delta time", "[Projectile][TDD]")
{
	ProjectileObject projectile;

	projectile.SetLifeTime(3.0f);
	projectile.ReduceLifeTime(-1.0f);

	REQUIRE(projectile.GetLifetime() == Catch::Approx(3.0f));
}

TEST_CASE("Projectile lifetime is unchanged by zero delta time", "[Projectile][TDD]")
{
	ProjectileObject projectile;

	projectile.SetLifeTime(3.0f);
	projectile.ReduceLifeTime(0.0f);

	REQUIRE(projectile.GetLifetime() == Catch::Approx(3.0f));
}