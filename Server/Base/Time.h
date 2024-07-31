#pragma once
#include <chrono>
#include <ctime>

using Milli_t = long long;
static const Milli_t INVALID_TIME = -1;
static const Milli_t INFINITE_TIME = LLONG_MAX;

namespace Time
{
    /// <summary>
    /// 현재 시간을 밀리초 단위로 반환합니다.
    /// </summary>
    /// <returns>현재 시간을 나타내는 밀리초 단위의 값입니다.</returns>
    const Milli_t GetCurrentMilliTick();

    /// <summary>
    /// 주어진 시점부터 경과된 시간을 반환합니다.
    /// </summary>
    /// <param name="tick">기준 시점을 나타내는 밀리초 단위의 값입니다.</param>
    /// <returns>기준 시점부터 현재 시점까지 경과된 시간을 밀리초 단위로 반환합니다.</returns>
    Milli_t GetElapsedTick(Milli_t tick);

    /// <summary>
    /// 현재 시점과 주어진 시점 간의 차이를 반환합니다.
    /// </summary>
    /// <param name="tick">비교할 시점을 나타내는 밀리초 단위의 값입니다.</param>
    /// <returns>현재 시점과 비교할 시점 간의 차이를 밀리초 단위로 반환합니다.</returns>
    Milli_t GetDiffedTick(Milli_t tick);

    /// <summary>
    /// 주어진 시점이 현재 시점을 지났는지 여부를 반환합니다.
    /// </summary>
    /// <param name="tick">비교할 시점을 나타내는 밀리초 단위의 값입니다.</param>
    /// <returns>주어진 시점이 이미 지났다면 true, 그렇지 않다면 false를 반환합니다.</returns>
    bool IsPast(Milli_t tick);

    /// <summary>
    /// 주어진 시점이 아직 오지 않았는지 여부를 반환합니다.
    /// </summary>
    /// <param name="tick">비교할 시점을 나타내는 밀리초 단위의 값입니다.</param>
    /// <returns>주어진 시점이 아직 오지 않았다면 true, 그렇지 않다면 false를 반환합니다.</returns>
    bool IsFeature(Milli_t tick);
}
