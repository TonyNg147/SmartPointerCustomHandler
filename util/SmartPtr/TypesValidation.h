#pragma once
#include <type_traits>
#include <iostream>

namespace TypeContraint
{
    template<typename F, typename T>
    concept IsTypeCompatible = std::is_same_v<F,T> || std::derived_from<T,F>;

    template<typename T>
    concept TypeSupportObservation = requires
    {
        typename T::SupportObservable;
    };
};

