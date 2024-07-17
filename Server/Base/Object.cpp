#include "Object.h"

bool CObject::CanDelete()
{
	return true;
}

void CObject::SafeDelete(CObject* object)
{
	if (false == object->CanDelete())
	{

	}
	else
	{
		delete object;
	}
}