#pragma once
#include "Thread.h"

class CObject;
class CObjectRecycler : public CSingleton<CObjectRecycler>
{
	SINGLETON_FOUNDATION(CObjectRecycler)

public:
	void Start();
	void Enqueue(CObject* object);

private:
	class CRecyclerThread;
	CRecyclerThread* m_Thread;
};

#define g_ObjectRecycler CSingleton<CObjectRecycler>::GetInstance()