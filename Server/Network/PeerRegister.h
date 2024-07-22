#pragma once
#include "Base/Singleton.h"
#include "PeerDef.h"

class CPeer;

class CPeerRegister : public CSingleton<CPeerRegister>
{
	SINGLETON_FOUNDATION(CPeerRegister)

private:
	CLock m_Lock;
	std::unordered_map<PeerId_t, CPeer*> m_PeerMap; ///< 등록된 피어들을 저장하는 리스트

public:
	/// <summary>
	 /// 피어를 등록합니다.
	 /// </summary>
	 /// <param name="peer"> 등록할 피어 객체 </param>
	void AddPeer(CPeer* peer);

	/// <summary>
	 /// 서버 종료시 피어들을 Disconnect 시킴
	 /// </summary>
	void Shutdown();
};


#define g_PeerRegister CSingleton<CPeerRegister>::GetInstance()