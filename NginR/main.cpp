#include "NginR/Engine.h"
#include "NginR/graphic-library-wrappers/GraphicLibraryWrapperFactory.h"



int main()
{
	Engine::GraphicLibraryWrapperFactory gFactory;
	auto mGLib = gFactory.getGraphicLibrary(Engine::OpenGL);
	Engine::Engine Enginar(mGLib, true);

	Enginar.startEngine();
	Enginar.playGame();

	return 0;
}
