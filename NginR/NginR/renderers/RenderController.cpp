#include "RenderController.h"


RenderController::RenderController()
{
	selectedStrategy = nullptr;
	Strategies = new RenderStrategy*[__EndOfNames__]();
}

RenderController::~RenderController()
{
	selectedStrategy = nullptr;
	for (int i = 0; i < __EndOfNames__;i++)
		delete [] Strategies[i];
	delete[] Strategies;
}

void RenderController::AddStrategy(RenderOptionNames key, RenderStrategy* strategy)
{
	Strategies[key] =  strategy;
}

bool RenderController::SetStrategy(RenderOptionNames key, void (*fnc)(char*))
{
	if (Strategies[key] != nullptr)
	{
		selectedStrategy = Strategies[key];

		char* mode = "Mode: ";
		char* name = selectedStrategy->GetName();
		char* text = new char[std::strlen(name) + 7];
		char* itr = text;
		while (*mode) *itr++ = *mode++;
		while (*name) *itr++ = *name++;
		*itr = '\0';

		fnc(text);
		delete text;
		return true;
	}
	return false;
}

ProcessorType RenderController::getProcessorType() const
{
	return selectedStrategy->getProcessorType();
}

void RenderController::Apply(World w, Vec3<int> ViewPort, unsigned int* dst) const
{
	if (this->selectedStrategy == nullptr)
		return;

	this->selectedStrategy->DrawNextFrame(w,ViewPort,dst);
}
