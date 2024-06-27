#pragma once
#include "Base/Component.h"

class CAsyncTcpEvent;
class CPeer;
class CMarshalerComponent : public CComponent
{
	COMPONENT_FOUNDATION(CMarshalerComponent);

protected:

	virtual void Init();

public:
	int UnMarshal(CPeer* peer, uint8_t* buffer, int ioByte);
};

