#include "GamePacketHandlerSetup.h"
#include "Network/HandlerRegistry.h"
#include "CG_LoginHandler.h"

void GamePacketHandlerSetup::Setup()
{
	g_HandlerRegistry::GetInstance()->Resist(CG_LoginHandler::GetEnum(), CG_LoginHandler::GetClone());
}
