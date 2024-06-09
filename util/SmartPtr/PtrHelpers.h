#pragma once
#include "SharedPtr.h"
#include <Impl.h>
#include "CountableObj.h"
template<typename Impl, typename... I>
using AppendCountableHelper = CountableObj<Impl,ImplementationSupport<Impl,I...>>;


template<typename F, typename T>
concept IsTypeCompatible = std::is_same_v<F,T> || std::derived_from<F,T>;
