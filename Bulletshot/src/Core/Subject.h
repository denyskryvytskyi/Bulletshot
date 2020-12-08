#pragma once

template<class Observer>
class Subject
{
public:
    void AddObserver(Observer* listener)
    {
        m_Observers.insert(listener);
    }
    void RemoveObserver(Observer* listener)
    {
        m_Observers.erase(listener);
    }

    template<class... FuncArgs, class... InvokeArgs>
    void NotifyObservers(void (Observer::* function)(FuncArgs...), InvokeArgs... args) {
        for (auto observer : m_Observers)
            (observer->*(function))(args...);
    }

private:
    std::set<Observer*> m_Observers;
};