#include "Network/Peer.h"
int main()
{
	typedef std::shared_ptr<CPeer> CPeerPtr;
	CPeer* peer = New(CPeer);

	CPeerPtr tester = std::make_shared<CPeer>();

	delete peer;
	tester.use_count();

	return 0;
}