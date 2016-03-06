#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* const argv[])
{
	int result = Catch::Session().run();
	std::getchar();
	return result;
}