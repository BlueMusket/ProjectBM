#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

using Milli_t = long long;
static const Milli_t INVALID_TIME = -1;
static const Milli_t INFINITE_TIME = LLONG_MAX;

namespace Tick
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


class CTime
{
public:
    CTime(bool isUTC = false);
    CTime(const SYSTEMTIME& st, bool isUTC);

    bool IsUTC() const;
    void SetToUTC();
    void SetToLocal();

    void AddYears(int years);
    void AddMonths(int months);
    void AddDays(int days);
    void AddHours(int hours);
    void AddMinutes(int minutes);
    void AddSeconds(int seconds);
    void AddMilliseconds(int milliseconds);

    std::string ToString(const std::string& format) const;
    ULONGLONG ToULONGLONG() const;
    static CTime FromULONGLONG(ULONGLONG value, bool isUTC);
    static CTime FromTickCount64(bool asUTC);
    ULONGLONG ToTickCount64() const;

private:
    ULONGLONG m_time; // 100-nanosecond intervals since January 1, 1601 (UTC)
    bool m_isUTC;

    void NormalizeTime();
    static ULONGLONG GetSystemStartTime();
    static ULONGLONG SystemTimeToULONGLONG(const SYSTEMTIME& st);
    static void ULONGLONGToSystemTime(ULONGLONG time, SYSTEMTIME& st);
};