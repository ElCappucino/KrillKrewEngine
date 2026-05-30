#include "catch_amalgamated.hpp"
#include "../Timer.h"

#include <cmath>
#include <thread>
#include <chrono>

TEST_CASE("Timer clamps negative time scale to zero", "[Timer][TDD]")
{
	Timer* timer = Timer::Instance();

	timer->setTimeScale(-1.0f);

	REQUIRE(timer->getTimeScale() == Catch::Approx(0.0f));
}

TEST_CASE("Timer keeps valid positive time scale", "[Timer][TDD]")
{
	Timer* timer = Timer::Instance();

	timer->setTimeScale(1.5f);

	REQUIRE(timer->getTimeScale() == Catch::Approx(1.5f));
}

TEST_CASE("Timer resets NaN time scale to default", "[Timer][TDD]")
{
	Timer* timer = Timer::Instance();

	timer->setTimeScale(std::nanf(""));

	REQUIRE(timer->getTimeScale() == Catch::Approx(1.0f));
}

TEST_CASE("Timer resets infinity time scale to default", "[Timer][TDD]")
{
	Timer* timer = Timer::Instance();

	timer->setTimeScale(INFINITY);

	REQUIRE(timer->getTimeScale() == Catch::Approx(1.0f));
}

TEST_CASE("Timer accepts zero time scale", "[Timer][TDD]")
{
	Timer* timer = Timer::Instance();

	timer->setTimeScale(0.0f);

	REQUIRE(timer->getTimeScale() == Catch::Approx(0.0f));
}

TEST_CASE("Timer reset clears delta time and fps", "[Timer][TDD]")
{
	Timer* timer = Timer::Instance();

	timer->setTimeScale(1.0f);
	timer->reset();

	REQUIRE(timer->getDeltaTime() == Catch::Approx(0.0f));
	REQUIRE(timer->getFps() == Catch::Approx(0.0f));
}

TEST_CASE("Timer tick produces zero delta time when time scale is zero", "[Timer][TDD]")
{
	Timer* timer = Timer::Instance();

	timer->reset();
	timer->setTimeScale(0.0f);

	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	timer->tick();

	REQUIRE(timer->getDeltaTime() == Catch::Approx(0.0f));
}