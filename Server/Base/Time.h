#pragma once
#include <chrono>
#include <ctime>

using Milli_t = long long;
static const Milli_t INVALID_TIME = -1;
static const Milli_t INFINITE_TIME = LLONG_MAX;

namespace Time
{
    /// <summary>
    /// 현재 시간을 밀리초 단위로 반환
    /// </summary>
    /// <returns>현재 시간을 나타내는 밀리초</returns>
    const Milli_t GetCurrentMilliTick();

    /// <summary>
    /// 주어진 밀리초 시간에 현재 시간을 더한 값을 반환
    /// </summary>
    /// <param name="tick"> 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간에 tick 값을 더한 밀리초 시간</returns>
    Milli_t GetElapsedTick(Milli_t tick);

    /// <summary>
    /// 주어진 밀리초 시간과 현재 시간의 차이를 반환
    /// </summary>
    /// <param name="tick"> 비교할 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간과 tick 시간의 차이를 나타내는 밀리초 값</returns>
    Milli_t GetDiffedTick(Milli_t tick);

    /// <summary>
    /// 주어진 시간이 현재 시간보다 과거인지 확인
    /// </summary>
    /// <param name="tick"> 확인할 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간보다 과거이면 true, 아니면 false</returns>
    bool IsPast(Milli_t tick);

    /// <summary>
    /// 주어진 시간이 현재 시간보다 미래인지 확인
    /// </summary>
    /// <param name="tick"> 확인할 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간보다 미래이면 true, 아니면 false</returns>
    bool IsFeature(Milli_t tick);
}
