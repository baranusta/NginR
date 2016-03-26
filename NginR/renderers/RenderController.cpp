#include "RenderController.h"


RenderController::RenderController()
{
	selectedStrategyKey = __RENDER_NAME_SIZE__;
	Strategies = new RenderStrategy*[__RENDER_NAME_SIZE__]();
	for (int i = 0; i < __RENDER_NAME_SIZE__; i++)
		Strategies[i] = nullptr;
}

RenderController::~RenderController()
{
	for (auto observer : observers)
		observer->removeObservable(this);
	for (int i = 0; i < __RENDER_NAME_SIZE__; i++)
		delete Strategies[i];
	delete Strategies;
}

void RenderController::AddStrategy(RenderOptionNames key, RenderStrategy* strategy)
{
	if (key >= __RENDER_NAME_SIZE__)
		throw Exception(NO_SUCH_RENDER_OPTION);
	selectedStrategyKey = key;
	if (Strategies[key] != nullptr)
	{
		delete Strategies[key];
	}
	Strategies[key] = strategy;
}

bool RenderController::SetStrategy(RenderOptionNames key)
{
	if (Strategies[key] != nullptr && key != selectedStrategyKey)
	{
		selectedStrategyKey = key;
		publishRenderOptionChanged(key, Strategies[key]->GetName());
		return true;
	}
	return false;
}

void RenderController::attachObserver(Observer* vable)
{
	Observable::attachObserver(vable);
	if (IRenderOptionChangedObserver* c = dynamic_cast<IRenderOptionChangedObserver*>(vable))
	{
		c->notifyRenderOptionNameChanged(selectedStrategyKey, Strategies[selectedStrategyKey]->GetName());
	}
}

ProcessorType RenderController::getProcessorType() const
{
	return Strategies[selectedStrategyKey]->getProcessorType();
}

void RenderController::publishRenderOptionChanged(RenderOptionNames key, char* text)
{
	for (Observer* obs : observers)
		if (IRenderOptionChangedObserver* c = dynamic_cast<IRenderOptionChangedObserver*>(obs))
		{
			c->notifyRenderOptionNameChanged(key, text);
		}
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
	if (selectedStrategyKey == __RENDER_NAME_SIZE__)
		return;

	Strategies[selectedStrategyKey]->DrawNextFrame(light,
		objects,
		src,
		dst,
		camPos,
		distance,
		width,
		height);
}

void RenderController::updateStaticScene(const std::vector<GameObject*>& objects, const std::vector<Light>& lights, int width, int height)
{
	Strategies[selectedStrategyKey]->updateStaticScene(objects,lights,width,height);
}
