#pragma once
#include "Base/Singleton.h"
#include "Handler.h"
#include <map>

class CHandlerRegistry : public CSingleton<CHandlerRegistry>
{
public:
	CHandlerRegistry();
	virtual ~CHandlerRegistry();

public:
	void Resist(int id, CHandler* handler);
	CHandler* Find(int id);

private:
	std::map<int, CHandler*> m_List;
};

#define g_HandlerRegistry CSingleton<CHandlerRegistry>::GetInstance()