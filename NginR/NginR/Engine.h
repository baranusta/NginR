#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <vector>

#include "GameLooper.h"
#include "viewutils/FrameTextViewGL.h"

namespace Engine
{
	class GraphicLibraryWrapper;

	class Engine
	{
	public:

		explicit Engine(GraphicLibraryWrapper* mGraphicLib, bool startWithCuda);
		~Engine();
		void setTextViews(const std::vector<TextViewGL*> & textViewArr);
		void startEngine();

		void playGame() const;

	private:
		template <class T>
		void DeleteArray(std::vector<T> arr);
		bool isCudaAvailable() const;
		void initializeLoopFunctions();

		GraphicLibraryWrapper* graphicLib;
		GameLooper mainLooper;
	};


}
#endif
