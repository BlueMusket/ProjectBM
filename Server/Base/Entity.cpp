#include "Entity.h"
#include "Component.h"

CEntity::CEntity()
{
}

CEntity::~CEntity()
{
	for (auto component : m_ComponentList)
	{
		delete component.second;
	}
}