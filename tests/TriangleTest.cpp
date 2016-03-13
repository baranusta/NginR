#include "catch.hpp"
#include <world/objects-cpu/game-objects/Triangle.h>

TEST_CASE("Triangle Test") {
	Triangle wow(Vec3<float>(3,0,0), Vec3<float>(0,-3,0), Vec3<float>(0,3,0));
	SECTION("Normal calculation") {
		const Vec3<float> normal = wow.getNormal(Vec3<float>(0, -3, 0));
		REQUIRE(normal == Vec3<float>(0, 0, 1));
	}
}