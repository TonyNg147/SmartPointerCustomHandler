#pragma once
#include <StackAllocationDetection.h>
#include <stdexcept>
#include <iostream>
template<typename OriginalType, typename T>
class CountableObj: public T
{

public:
    using PtrObj = CountableObj<OriginalType,T>;

    CountableObj()
    {
        if (util::isAllocatedOnTheThreadStack(this))
        {
            throw std::runtime_error("Implementation for this class cannot be created on Stack!");
        }
    }

    void ref() override
    {
        ++m_count;
    }

    void unref() override
    {
        std::cout << "Call unref in Countable Object " << m_count << "\n";
        // Need to upper cast to the Original Type to call the upmost destructor first
        // then fails down to the inheritance chain
        // Otherwise, It ingores the Original Type and starts from the CountableObj
        if (--m_count == 0)
        {
            delete reinterpret_cast<OriginalType*>(this);
        }
    }

protected:

    std::atomic<int> m_count;
};
