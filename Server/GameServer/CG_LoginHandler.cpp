#include "CG_LoginHandler.h"


int CG_LoginHandler::Execute(CPeer* peer, uint8_t* buffer, int len)
{
	CPacketReader<CG_Login> reader(buffer);

	return 0;
}