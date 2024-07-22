#pragma once

namespace Genaric
{
	template<typename BASE, typename DERIVED>
	struct IsBaseOf { enum { Value = std::is_base_of<BASE, DERIVED>::value }; };

	// 동적 할당 관리
	class CNewable
	{

	};

	// 사용방법
	// static_assert(CanNew<T>::Value, "너는 동적할당 할 수 없다.", __FUNCSIG__);
	template<typename T>
	struct CanNew { enum {Value = IsBaseOf<T, CNewable>::value }; };
}