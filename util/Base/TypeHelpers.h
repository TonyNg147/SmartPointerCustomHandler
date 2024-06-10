#ifndef TYPEHELPERS_H
#define TYPEHELPERS_H
#include <type_traits>
namespace TypeHelpers
{
    template<typename T, typename=void>
    struct TypeHelperWrapper: std::false_type
    {
        using Type = T;
    };
    template<typename T>
    struct TypeHelperWrapper<T, std::void_t<typename T::HelperClassFor>>
    {
        using Type = T::HelperClassFor;
    };

    template<typename T>
    using TypeParsed = TypeHelperWrapper<T>::Type;
};

#endif // TYPEHELPERS_H
