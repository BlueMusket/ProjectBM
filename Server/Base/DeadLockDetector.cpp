#include "DeadLockDetector.h"

bool CDeadLockDetector::Setup()
{

    return true;
}

bool CDeadLockDetector::DetectCycle(const void* currentLock, const void* targetLock, std::unordered_set<const void*>& visited)
{
	if (currentLock == targetLock)
	{
		return true;
	}

	if (visited.count(currentLock) > 0)
	{
		return false;
	}

	visited.insert(currentLock);
	for (const auto& nextLock : m_LockOrder[currentLock])
	{
		if (DetectCycle(nextLock, targetLock, visited))
		{
			return true;
		}
	}
	return false;
}

void CDeadLockDetector::LockAcquired(const void* lockAddress)
{
    CScopeLock lock(&m_Lock);

    ThreadId_t threadId = Lock::GetCurrentThreadId();

    if (!m_ThreadLocks[threadId].empty())
    {
        const void* prevLock = m_ThreadLocks[threadId].back();

        if (m_LockOrder[prevLock].insert(lockAddress).second)
        {
            // 새로운 락 순서가 추가되었을 때만 순환 검사
            std::unordered_set<const void*> visited;
            if (DetectCycle(lockAddress, prevLock, visited))
            {
                throw std::runtime_error("Potential deadlock detected: Circular lock dependency");
            }
        }
    }

    m_ThreadLocks[threadId].push_back(lockAddress);
}

void CDeadLockDetector::LockReleased(const void* lockAddress)
{
    CScopeLock lock(&m_Lock);

    ThreadId_t threadId = Lock::GetCurrentThreadId();

    auto it = m_ThreadLocks.find(threadId);
    if (it != m_ThreadLocks.end())
    {
        auto& locks = it->second;
        locks.erase(std::remove(locks.begin(), locks.end(), lockAddress), locks.end());

        if (locks.empty())
        {
            m_ThreadLocks.erase(it);
        }
    }
}