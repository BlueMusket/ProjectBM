#pragma once
#include "Entity.h"

/// <summary>
/// ECS의 Component 최상위 클래스
/// </summary>
class CComponent
{
private:
	CEntity* m_Owner;

	template<typename T>
	T* GetOwner()
	{
		static_assert(std::is_base_of<CEntity, T>::value, "T must be derived from CEntity");
		return static_cast<T>(m_Owner);
	}

public:
	CComponent(CEntity* owner)
		: m_Owner(owner)
	{}
	virtual ~CComponent() {};
};

#define COMPONENT_FOUNDATION(name)\
public:\
	name(CEntity* owner); \
	virtual ~name(); \
	static std::string	GetName() { return #name; }\
	static int			GetHash() { return (int)std::hash<std::string>()(#name); } \
	static CComponent* GetClone(CEntity* owner) \
	{ \
		return new name(owner); \
	}