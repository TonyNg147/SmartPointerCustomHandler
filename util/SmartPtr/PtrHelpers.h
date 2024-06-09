#pragma once
#include "SharedPtr.h"
#include <Impl.h>
#include "CountableObj.h"
template<typename Impl, typename... I>
using AppendCountableHelper = CountableObj<Impl,ImplementationSupport<Impl,I...>>;



