#pragma once

class CAsyncEventSink;
class CPeerFacade
{
public:
	static void Disconnected(CAsyncEventSink* sink);
};

