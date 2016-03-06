#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* const argv[])
{
	try
	{

		int result = Catch::Session().run();
	}
	catch (...)
	{
		std::getchar();
	}
	std::getchar();
	return 0;
}