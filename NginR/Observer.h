#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <forward_list>

class Observable;

class Observer
{
public:
	void addObservable(Observable* vable)
	{
		observables.push_front(vable);
	}

	void removeObservable(Observable* vable)
	{
		observables.remove(vable);
	}

private:
	std::forward_list<Observable*> observables;
};

class Observable
{
public:
	virtual ~Observable()
	{
		
	}

	void registerObservingEvent(Observable* vable)
	{
		registerForEvent(vable);
	}
	virtual void unregisterObservingEvent(Observable* vable) = 0;

private:
	void registerForEvent(Observable* vable);

};


#endif