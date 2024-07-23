#pragma once

#include "System.h"
#include "MemoryEntity.h"

class CMemorySystem : public CSystem
{
SINGLETON_FOUNDATION(CMemorySystem)

public:
	template<typename T, typename... Types>
	T* Alloc(Types&&... args)
	{
		return m_MemoryEntity->Alloc<T>(std::forward<Types>(args)...);
	}

private:
	CMemoryEntity* m_MemoryEntity;
};

#define g_MemorySystem CSingleton<CMemorySystem>::GetInstance()