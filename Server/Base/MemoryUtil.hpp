#include "MemoryUtil.h"
#include "MemorySystem.h"

namespace MemoryUtil
{
	template<typename T, typename... Types>
	T* Alloc(Types&&... args)
	{
		return g_MemorySystem::GetInstance()->Alloc<T>(std::forward<Types>(args)...);
	}
}
