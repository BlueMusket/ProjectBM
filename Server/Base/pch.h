// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#pragma once

// 공용 헤더
// window 기본 헤더
#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_
#include <WinSock2.h>
#include <winsock.h>
#include <WS2tcpip.h>
#include <mswsock.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"mswsock.lib")


#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>

#include <string>
#include <algorithm>

// lib 헤더
// TBB
#include "tbb/concurrent_hash_map.h"
#include "tbb/concurrent_unordered_set.h"
#include "tbb/concurrent_queue.h"
#include "tbb/concurrent_priority_queue.h"

// 커스텀 헤더
#include "Time.h"
#include "Math.h"
#include "Genaric.h"
#include "Lock.h"
#include "BitBase.h"
#include "Atomic.h"
#include "Delegate.h"
#include "MemoryUtil.h"

#include "Thread.h"
#include "Task.h"
#include "Pool.h"