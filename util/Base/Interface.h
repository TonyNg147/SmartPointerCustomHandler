#pragma once
#include <type_traits>
#include <string.h>
#include <iostream>
#include <TypeHelpers.h>
class InterfaceID
{
    public:
        InterfaceID(const char* id)
            :m_id{id}
        {

        }

        InterfaceID(const InterfaceID& o)
            :m_id{o.m_id}
        {

        }

        const char* name() const
        {
            return m_id;
        }

        bool operator==(const InterfaceID& o) const
        {
            return std::string(m_id) == std::string(o.m_id);
        }
        bool operator<(const InterfaceID& o) const
        {
            return std::string(m_id) < std::string(o.m_id);
        }

    private:

        const char* m_id;
};  

class Interface
{
    public:
        virtual void ref(){};

        virtual void unref(){};

        virtual uint32_t refCount(){return 0;};

        virtual void* cast(InterfaceID) = 0;
};

template<typename>
inline const char* g_interface_query();

#define REGISTER_GLOBAL_INTERFACE(N)\
struct Interface_##N                 \
{                                   \
inline static const char* name = #N;  \
};                                  \
template<>                          \
inline const char* g_interface_query<N>()  {return Interface_##N::name;}





template<typename>
struct InterfaceDefinedID: std::false_type{};

template<typename T>
inline InterfaceID iid_impl()
{
    static_assert(InterfaceDefinedID<T>::value, "The Interface ID must be registered with REGISTER_SYS_INTERFACE");
    return g_interface_query<T>();
}

template<typename T>
inline InterfaceID iid = iid_impl<T>();


#define REGISTER_SYS_INTERFACE(N) \
REGISTER_GLOBAL_INTERFACE(N);     \
template<>\
struct InterfaceDefinedID<N>: std::true_type{};






template<typename TO, typename FROM>
TO* qi(FROM* to)
{
    static_assert(std::is_base_of_v<Interface, FROM> && std::is_base_of_v<Interface, TO>);
    return reinterpret_cast<TO*>(to->cast(iid<TypeHelpers::TypeParsed<TO>>));
};

REGISTER_SYS_INTERFACE(Interface);
