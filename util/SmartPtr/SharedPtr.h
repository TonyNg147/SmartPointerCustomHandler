#pragma once
#include <type_traits>
#include <iostream>
/**
    The Normal shared pointer attaches the handler for counting and managing 
    lifecycle of the instance inside the class. This can be rigid and hard for the customization
    because it allows to be used by all the type. When separating the handler for counting and managing
    we can control the usage of this SharePtr more effectively
 */
template<typename T>
class SharedPtr
{
    public:
        using Ptr_helper_for = T;

        SharedPtr() = default;

        SharedPtr(T* obj)
        {
            if(obj)
            {
                m_obj = obj;
                m_obj->ref();
            }
        }
        SharedPtr(const SharedPtr<T>& o)
        {
            m_obj = o.m_obj;
            if (m_obj)
            {
                m_obj->ref();
            }
        }

        template<typename O> requires IsTypeCompatible<O,T>
        SharedPtr(const SharedPtr<O>& o)
        {
            m_obj = o.m_obj;
            if (m_obj)
            {
                m_obj->ref();
            }
        }

        SharedPtr& operator=(const SharedPtr& o)
        {
            m_obj = o.m_obj;
            if (m_obj)
            {
                m_obj->ref();
            }
            return *this;
        }

        ~SharedPtr()
        {
            if (m_obj)
            {
                m_obj->unref();
            }
        }

        T* get() const
        {
            return reinterpret_cast<T*>(m_obj);
        }

        /**
            Cast to the other type
         */
        template<typename O>
        O* get() const
        {
            if constexpr (std::is_same_v<O,T>)
            {
                return get();
            }
            return qi<O>(m_obj);
        }

    private:

        T* m_obj = nullptr;

};

template<typename T, typename... Args>
SharedPtr<T> makeRef(Args... args)
{
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}
