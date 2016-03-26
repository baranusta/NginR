#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <forward_list>

class Observable;

class Observer
{
public:
	virtual ~Observer()
	{
		
	}
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
		for (auto observer : observers)
			observer->removeObservable(this);
	}

	void registerObservingEvent(Observer*vable)
	{
		observers.push_front(vable);
	}
	void unregisterObservingEvent(Observer* vable)
	{
		observers.remove(vable);
	}

protected:

	std::forward_list<Observer*> observers;

};


#endif