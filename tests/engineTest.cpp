#include "catch.hpp"
#include <Engine.h>
#include <iostream>

TEST_CASE("Engine is under test") {
	Engine::Engine t;
	SECTION("Engine started without game should throw exception") {
		try{
			t.startEngine();
		}
		catch (Exception & exception)
		{
			std::string message = exception.what();
			REQUIRE(message == ENGINE_NO_GAME_EXCEPTION);
		}
	}
}