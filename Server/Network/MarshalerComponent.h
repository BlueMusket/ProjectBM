#pragma once
#include "Base/Component.h"

class CPeer;
class CMarshalerComponent : public CComponent
{
	COMPONENT_FOUNDATION(CMarshalerComponent);

public:
	int UnMarshal(CPeer* peer, uint8_t* buffer, int ioByte);
};

