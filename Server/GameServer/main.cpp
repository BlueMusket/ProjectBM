#include "GameServerAppManager.h"
#include "Server/TimerShard.h"

int main()
{
	g_GameServerAppManager->Setup();

	// TODO : IsAppTerminated
	while (true)
	{
		Milli_t current = CTime::GetTickCount64();

		g_TimerShard->HeartBeat(current);

		Milli_t duration = CTime::GetTickCount64() - current;

		// 너무 길면 로그

		Milli_t waitTick = Math::Max((Milli_t)100 - duration, (Milli_t)0);

		Sleep((DWORD)waitTick);
	}

	return 0;
}