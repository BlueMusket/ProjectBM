#include "Object.h"
#include "Base/ObjectRecycler.h"

CObject::CObject()
	: m_IsDeleted(false)
{
	m_Self = CObjectPtr(this, CObject::SafeDelete);
}

CObject::~CObject()
{
}

bool CObject::CanDelete()
{
	return true;
}

void CObject::ReleaseSelf()
{
	if (m_IsDeleted.CompareAndExchange(false, true))
	{
		CObjectPtr empty;

		m_Self.swap(empty);
		empty.reset();
	}
}

void CObject::SafeDelete(CObject* object)
{
	g_ObjectRecycler->Enqueue(object);
}