#pragma once

#include "Singleton.h"
#include "MemoryEntity.h"
#include "Pool.h"

class CMemorySystem : public CSingleton<CMemorySystem>
{
SINGLETON_FOUNDATION(CMemorySystem)

public:
	template<typename T, typename... Types>
	T* Alloc(Types&&... args)
	{
		//return m_MemoryEntity->Alloc<T>(std::forward<Types>(args)...);

		if constexpr (Is_UsePool<T>::value)
		{
			// T가 Pool을 사용하는 타입일 경우
			return PoolClassName<T>::type::Get(std::forward<Types>(args)...);
		}
		else
		{
			return new T(std::forward<Types>(args)...);
		}
	}

	template<typename T>
	void Dealloc(T* item)
	{
		if constexpr (Is_UsePool<T>::value)
		{
			// T가 Pool을 사용하는 타입일 경우
			PoolClassName<T>::type::Put(item);
		}
		else
		{
			if constexpr (std::is_array_v<T>)
			{
				delete[] item;
			}
			else
			{
				delete item;
			}
		}
	}

private:
	CMemoryEntity* m_MemoryEntity;
};

#define g_MemorySystem CSingleton<CMemorySystem>::GetInstance()