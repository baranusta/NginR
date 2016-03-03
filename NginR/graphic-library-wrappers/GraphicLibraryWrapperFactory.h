#ifndef _GRAPHICLIBRARYFACTORY_H_
#define _GRAPHICLIBRARYFACTORY_H_

#include "opengl-wrapper/OpenGLWrapper.h"

namespace Engine
{
	enum GraphicLibraryName{ OpenGL, DirectX };

	class GraphicLibraryWrapperFactory
	{
	public:
		GraphicLibraryWrapper* getGraphicLibrary(GraphicLibraryName name, int width = 768, int height = 512)
		{
			switch (name)
			{
			case OpenGL:
				return new OpenGLWrapper(width,height);
				break;
			case DirectX:
				return nullptr;
				break;
			default:
				break;
			}
			return nullptr;
		}

	};
}


#endif
