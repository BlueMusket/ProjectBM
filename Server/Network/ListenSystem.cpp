#include "ListenSystem.h"

CListenSystem::CListenSystem()
	: m_Listener(nullptr)
{
}

CListenSystem::~CListenSystem()
{
}

void CListenSystem::Init(CPeerListener* listener)
{
	m_Listener = listener;
}

void CListenSystem::Start()
{
	m_Listener->Start();
}
