#pragma once

//#include "Component.h"

class CComponent;

/// <summary>
/// Component(도구 - 기능)를 사용할 사용자 ( Peer, ...er , System 등 )의 최상위 클래스
/// </summary>
class CEntity
{
public:
	CEntity();
	virtual ~CEntity();

private:
	std::unordered_map<int, CComponent*> m_ComponentList;

public:
	template< typename T>
	T* GetComponent()
	{
		const int hash = T::GetHash();
		auto findItor = m_ComponentList.find(hash);

		if (m_ComponentList.end() == findItor)
		{
			return nullptr;
		}

		return static_cast<T*>(findItor->second);
	}

protected:
	template< typename T>
	void InsertComponent()
	{
		m_ComponentList.insert(std::make_pair(T::GetHash(), T::GetClone()));
	}
};