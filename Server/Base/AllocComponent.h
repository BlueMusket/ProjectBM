#pragma once

#include "Component.h"

class CAllocComponent : public CComponent
{
	COMPONENT_FOUNDATION(CAllocComponent)

public:
	template<typename T, typename... Types>
	T* Alloc(Types&&... args)
	{
		return new T(std::forward<Types>(args)...);
	}
};

