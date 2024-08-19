#pragma once

namespace MemoryUtil
{
	template<typename T, typename... Types>
	T* Alloc(Types&&... args);

	template<typename T>
	void Dealloc(T* item);
}


#include "MemoryUtil.hpp"

#define New(name , ...) MemoryUtil::Alloc<name>(__VA_ARGS__)
#define Delete(item) MemoryUtil::Dealloc(item)