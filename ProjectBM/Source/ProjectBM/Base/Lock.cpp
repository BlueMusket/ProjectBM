// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock.h"

CLock::CLock()
{
}

CLock::~CLock()
{
    // 락이 해제되지 않은 상태로 객체가 소멸될 경우를 대비하여, 소멸자에서 해제를 시도합니다.
    Unlock();
}

void CLock::Lock()
{
    CriticalSection.Lock();
}

void CLock::Unlock()
{
    CriticalSection.Unlock();
}


CScopeLock::CScopeLock(CLock& InLock)
    : Lock(InLock)
{
    // 생성자에서 락을 획득합니다.
    Lock.Lock();
}

CScopeLock::~CScopeLock()
{
    // 소멸자에서 락을 해제합니다.
    Lock.Unlock();
}
