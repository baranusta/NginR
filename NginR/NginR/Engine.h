#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <vector>

#include "graphic-library-wrappers/GraphicLibraryWrapperFactory.h"
#include "Game.h"
#include "viewutils/FrameTextViewGL.h"

namespace Engine
{
	class GraphicLibraryWrapper;

	class Engine
	{
	public:
		explicit Engine();
		explicit Engine(const GraphicLibraryName & libName, bool showFrame = true);
		~Engine();
		void setGame(Game* game);
		void addTextViews(const std::vector<TextViewGL*> & textViewArr);
		void startEngine() const;

	private:
		void _constructEngine(const GraphicLibraryName & libName, bool showFrame);
		template <class T>
		void _deleteArray(std::vector<T> arr);
		bool _isCudaAvailable() const;
		void _initializeLoopFunctions();

		GraphicLibraryWrapper* graphicLib;
	};


}
#endif
