#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include <Interface.h>
#include <list>

class Observer
{
public:
    virtual void resetObservable() = 0;
    virtual void doSubscribe() = 0;
    virtual void doUnSubscribe() = 0;
};

class Observable: public Interface
{
public:
    using SupportObservable = Observable;

    virtual void* cast(InterfaceID id) override
    {
        if (id == iid<Observable>)
        {
            return reinterpret_cast<void*>(this);
        }
        return nullptr;
    }

    virtual void subscribe(Observer*) = 0;
    virtual void unsubscribe(Observer*) = 0;
protected:
    virtual void disconnectAll() = 0;
};

REGISTER_SYS_INTERFACE(Observable);

class ObservableImpl: public Observable
{
public:
    using HelperClassFor = Observable;

    virtual void subscribe(Observer*) override;

    virtual void unsubscribe(Observer*) override;

private:
    virtual void disconnectAll() override;

private:
    std::list<Observer*> m_observers;
};

REGISTER_SYS_INTERFACE(ObservableImpl);

#endif //OBSERVABLE_H
