#include "GamePacketHandlerSetup.h"

#include "Network/HandlerRegistry.h"

void GamePacketHandlerSetup::Setup()
{
	g_HandlerRegistry::GetInstance()->Resist(CT_LoginHandler::GetHash(), CT_LoginHandler::GetClone());
	g_HandlerRegistry::GetInstance()->Resist(TQ_LoginHandler::GetHash(), TQ_LoginHandler::GetClone());
	g_HandlerRegistry::GetInstance()->Resist(CT_PingHandler::GetHash(), CT_PingHandler::GetClone());
}
