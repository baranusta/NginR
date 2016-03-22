#include "RenderController.h"


RenderController::RenderController()
{
	selectedStrategy = nullptr;
	Strategies = new RenderStrategy*[__RENDER_NAME_SIZE__]();
	for (int i = 0; i < __RENDER_NAME_SIZE__; i++)
		Strategies[i] = nullptr;
}

RenderController::~RenderController()
{
	for (auto observer : observers)
		observer->removeObservable(this);
	selectedStrategy = nullptr;
	for (int i = 0; i < __RENDER_NAME_SIZE__; i++)
		delete [] Strategies[i];
	delete[] Strategies;
}

void RenderController::registerObservingEvent(IRenderOptionChangedObserver* vable)
{
	observers.push_front(vable);
}

void RenderController::unregisterObservingEvent(Observable* vable)
{
	if (IRenderOptionChangedObserver* c = dynamic_cast<IRenderOptionChangedObserver*>(vable))
	{
		observers.remove(c);
	}
}

void RenderController::AddStrategy(RenderOptionNames key, RenderStrategy* strategy)
{
	if (key >= __RENDER_NAME_SIZE__)
		throw Exception(NO_SUCH_RENDER_OPTION);
	if (Strategies[key] != nullptr)
	{
		delete Strategies[key];
		Strategies[key] = strategy;
	}

	Strategies[key] = strategy;

	if (selectedStrategy == nullptr)
		selectedStrategy = strategy;
}

bool RenderController::SetStrategy(RenderOptionNames key)
{
	if (Strategies[key] != nullptr)
	{
		RenderStrategy* newlySelected = Strategies[key];
		if (newlySelected->getProcessorType() != selectedStrategy->getProcessorType())
		{
			char* mode = "Mode: ";
			char* name = selectedStrategy->GetName();
			char* text = new char[std::strlen(name) + 7];
			char* itr = text;
			while (*mode) *itr++ = *mode++;
			while (*name) *itr++ = *name++;
			*itr = '\0';

			delete text;
			for (IRenderOptionChangedObserver* obs : observers)
				obs->publishProcessorTypeChanged(key,text);
		}
		selectedStrategy = newlySelected;
		return true;
	}
	return false;
}

ProcessorType RenderController::getProcessorType() const
{
	return selectedStrategy->getProcessorType();
}

void RenderController::Apply(const Light & light,
	const std::vector<GameObject*>& objects,
	unsigned int* src,
	unsigned int* dst,
	const Vec3<float>& camPos,
	int distance,
	int width,
	int height) const
{
	if (this->selectedStrategy == nullptr)
		return;

	this->selectedStrategy->DrawNextFrame(light,
		objects,
		src,
		dst,
		camPos,
		distance,
		width,
		height);
}
