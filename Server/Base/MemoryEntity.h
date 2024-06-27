#pragma once

#include "Entity.h"
#include "AllocComponent.h"

class CMemoryEntity : public CEntity
{
public:
	CMemoryEntity();
	virtual ~CMemoryEntity();

public:
	template<typename T, typename... Types>
	T* Alloc(Types&&... args)
	{
		CAllocComponent* component = GetComponent<CAllocComponent>();
		return component->Alloc<T>(std::forward<Types>(args)...);
	}
};