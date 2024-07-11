#pragma once

using ThreadId_t = std::thread::id;

namespace Lock
{
	inline ThreadId_t GetCurrentThreadId()
	{
		return std::this_thread::get_id();
	}
}