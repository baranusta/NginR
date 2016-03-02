#include "catch.hpp"
#include <Engine.h>

class EngineTester
{
public:
	EngineTester()
	{
		wow = new Engine::Engine();
	}
private:
	Engine::Engine* wow;
};

TEST_CASE("Engine is under test") {
	EngineTester t;
	REQUIRE(true);
	SECTION("Engine started without game should throw exception") {
		REQUIRE(true);
		/*try{
			Enginar.startEngine();
		}
		catch (Exception const & exception)
		{
			REQUIRE(exception.what() == ENGINE_NO_GAME_EXCEPTION);
		}*/
	}
}