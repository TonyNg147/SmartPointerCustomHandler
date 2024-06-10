#include "Observable.h"
void ObservableImpl::subscribe(Observer *o)
{
    if (o)
    {
        m_observers.push_back(o);
    }
}

void ObservableImpl::unsubscribe(Observer *o)
{
    if (o)
    {
        auto it = m_observers.begin();
        while(it != m_observers.end())
        {
            if (*it == o)
            {
                m_observers.erase(it);
                break;
            }
            ++it;
        }
    }
}

void ObservableImpl::disconnectAll()
{
    for (auto& o: m_observers)
    {
        o->resetObservable();
    }
    m_observers.clear();
}
