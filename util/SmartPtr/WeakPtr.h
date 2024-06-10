#pragma once
#include <type_traits>
#include <iostream>
#include "TypesValidation.h"
#include "SharedPtr.h"
#include "Observable.h"
#include <Interface.h>
#include <exception>
template<TypeContraint::TypeSupportObservation T>
class WeakPtr: public Observer
{
public:
    WeakPtr()
    {
        m_obj = nullptr;
    }
    ~WeakPtr()
    {
        if (m_obj)
        {
            doUnSubscribe();
        }
    }

    WeakPtr(const SharedPtr<T>& sharedPtr)
    {
        m_obj = sharedPtr.get();
        if (m_obj)
        {
            m_obj->subscribe(this);
        }
    }

    void reset()
    {
        if (m_obj)
        {
            m_obj->unscribe(this);
        }
        m_obj = nullptr;
    }

    void resetObservable() override
    {
        m_obj = nullptr;
    }


    SharedPtr<T> lock() const
    {
        return SharedPtr<T>(m_obj);
    }
protected:
    void doSubscribe() override
    {
        auto observable = qi<Observable>(m_obj);
        if (observable == nullptr)
        {
            throw std::runtime_error("Must provide the cast to Observable");
        }
        observable->subscribe(this);
    }

    void doUnSubscribe() override
    {
        auto observable = qi<Observable>(m_obj);
        if (observable == nullptr)
        {
            throw std::runtime_error("Must provide the cast to Observable");
        }
        observable->unsubscribe(this);
    }


private:
    T* m_obj = nullptr;
};
