#include "MemoryUtil.h"
#include "MemorySystem.h"

namespace MemoryUtil
{
	template<typename T, typename... Types>
	T* Alloc(Types&&... args)
	{
		return g_MemorySystem->Alloc<T>(std::forward<Types>(args)...);
	}

	template<typename T>
	void Dealloc(T* item)
	{
		g_MemorySystem->Dealloc<T>(item);
	}
}
