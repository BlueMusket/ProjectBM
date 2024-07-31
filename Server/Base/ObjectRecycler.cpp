#include "ObjectRecycler.h"
#include "Object.h"


class CObjectRecycler::CRecyclerThread : public CThread
{
public:
	CRecyclerThread() : CThread(100) {}
	~CRecyclerThread() 
	{
		CObject* object = nullptr;
		while (m_RecycleQueue.try_pop(object))
		{
			delete object;
		}
	}

private:
	tbb::concurrent_queue<CObject*> m_RecycleQueue;

public:
	virtual void Execute()
	{
		CObject* object = nullptr;
		while (m_RecycleQueue.try_pop(object))
		{
			if (false == object->IsDeleted())
			{
				// 에러...
			}

			if (true == object->CanDelete())
			{
				delete object;
			}
			else
			{
				Enqueue(object);
			}
		}
	}

	virtual const wchar_t* GetName() { return L"ObjectRecycler Thread"; }

public:
	void Enqueue(CObject* object)
	{
		m_RecycleQueue.emplace(object);
	}
};

CObjectRecycler::CObjectRecycler()
{
	m_Thread = New(CObjectRecycler::CRecyclerThread);
}

CObjectRecycler::~CObjectRecycler()
{
}

void CObjectRecycler::Start()
{
	m_Thread->Init();
}

void CObjectRecycler::Enqueue(CObject* object)
{
	m_Thread->Enqueue(object);
}