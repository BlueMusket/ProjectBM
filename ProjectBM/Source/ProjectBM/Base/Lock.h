// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/CriticalSection.h"


/**
 * FMyLock 클래스는 FCriticalSection을 사용하여 스레드 간의 자원 접근을 동기화하는 기본적인 락 메커니즘을 제공합니다.
 */
class PROJECTBM_API CLock
{
public:
    // 생성자
    CLock();

    // 소멸자
    ~CLock();

    // 락 획득
    void Lock();

    // 락 해제
    void Unlock();

private:
    // Critical Section 객체
    FCriticalSection CriticalSection;
};


class PROJECTBM_API CScopeLock
{
public:
    // 생성자에서 락을 획득합니다.
    CScopeLock(CLock& InLock);

    // 소멸자에서 락을 해제합니다.
    ~CScopeLock();

private:
    // 참조된 FMyLock 객체
    CLock& Lock;
};

