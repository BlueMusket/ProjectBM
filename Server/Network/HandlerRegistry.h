#pragma once
#include "Base/Singleton.h"

class CHandler;
class CHandlerRegistry : public CSingleton<CHandlerRegistry>
{
	SINGLETON_FOUNDATION(CHandlerRegistry)

public:
	void Resist(int id, CHandler* handler);
	CHandler* Find(int id);

private:
	std::map<int, CHandler*> m_List;
};

#define g_HandlerRegistry CSingleton<CHandlerRegistry>::GetInstance()