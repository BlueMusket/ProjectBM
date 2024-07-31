#include "Network/Peer.h"
#include "Base/Task.h"
#include "Network/AsyncDispatcher.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Network/Peer.h"

int main()
{
	std::shared_ptr<CPeer> same;

	auto newPeer = New(CPeer); // 원본 생성 m_Self가 만들어 지면서 참조 카운트 1

	newPeer->ReleaseSelf();
	same = newPeer->GetSelf<CPeer>(); // 원본으로 새로운 SharedPtr을 만들며 참조 카운트 2

	return 0;
}