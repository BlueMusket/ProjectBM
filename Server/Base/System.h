#pragma once
#include "Singleton.h"
/// <summary>
/// ECS의 System 최상위 클래스
/// </summary>

class CSystem : public CSingleton<CSystem>
{
	SINGLETON_FOUNDATION(CSystem)

};

