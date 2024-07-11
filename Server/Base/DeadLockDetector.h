#pragma once
#include "Singleton.h"

class CDeadLockDetector : public CSingleton<CDeadLockDetector>
{
protected:
    virtual bool Setup() override;

private:
    CLock m_Lock;
    std::unordered_map<ThreadId_t, std::vector<const void*>> m_ThreadLocks;
    std::unordered_map<const void*, std::unordered_set<const void*>> m_LockOrder;

    bool DetectCycle(const void* currentLock, const void* targetLock, std::unordered_set<const void*>& visited);


public:
    void LockAcquired(const void* lockAddress);

    void LockReleased(const void* lockAddress);
};