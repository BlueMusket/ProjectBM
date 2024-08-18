#include "Time.h"
#include <ctime>
#include <iomanip>
#include <sstream>

const std::chrono::steady_clock::time_point CTime::s_StartTime = std::chrono::steady_clock::now();

CTime::CTime(bool isUTC) : m_TimePoint(std::chrono::system_clock::now()), m_IsUTC(isUTC) {}

CTime::CTime(int year, int month, int day, int hour, int minute, int second, int millisecond, bool isUTC)
    : m_IsUTC(isUTC)
{
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    m_TimePoint = FromTimeStruct(tm, isUTC) + std::chrono::milliseconds(millisecond);
}

CTime::CTime(Milli_t tickCount, bool isUTC) : m_IsUTC(isUTC)
{
    auto duration = std::chrono::milliseconds(tickCount);
    m_TimePoint = std::chrono::system_clock::now() + duration -
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - s_StartTime);
}

int CTime::GetYear() const { return GetTimeStruct(m_TimePoint, m_IsUTC).tm_year + 1900; }
int CTime::GetMonth() const { return GetTimeStruct(m_TimePoint, m_IsUTC).tm_mon + 1; }
int CTime::GetDay() const { return GetTimeStruct(m_TimePoint, m_IsUTC).tm_mday; }
int CTime::GetHour() const { return GetTimeStruct(m_TimePoint, m_IsUTC).tm_hour; }
int CTime::GetMinute() const { return GetTimeStruct(m_TimePoint, m_IsUTC).tm_min; }
int CTime::GetSecond() const { return GetTimeStruct(m_TimePoint, m_IsUTC).tm_sec; }
int CTime::GetMillisecond() const
{
    return std::chrono::time_point_cast<std::chrono::milliseconds>(m_TimePoint).time_since_epoch().count() % 1000;
}

bool CTime::IsUTC() const { return m_IsUTC; }

const TimePoint& CTime::GetTimePoint() const
{
    return m_TimePoint;
}

void CTime::AddYears(int years)
{
    auto tm = GetTimeStruct(m_TimePoint, m_IsUTC);
    tm.tm_year += years;
    m_TimePoint = FromTimeStruct(tm, m_IsUTC);
}

void CTime::AddMonths(int months)
{
    auto tm = GetTimeStruct(m_TimePoint, m_IsUTC);
    tm.tm_mon += months;
    m_TimePoint = FromTimeStruct(tm, m_IsUTC);
}

void CTime::AddDays(int days) { m_TimePoint += std::chrono::hours(24 * days); }
void CTime::AddHours(int hours) { m_TimePoint += std::chrono::hours(hours); }
void CTime::AddMinutes(int minutes) { m_TimePoint += std::chrono::minutes(minutes); }
void CTime::AddSeconds(int seconds) { m_TimePoint += std::chrono::seconds(seconds); }
void CTime::AddMilliseconds(int milliseconds) { m_TimePoint += std::chrono::milliseconds(milliseconds); }

Milli_t CTime::ToTickCount(CTime& time)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        (time.GetTimePoint() - std::chrono::system_clock::now()) +
        (std::chrono::steady_clock::now() - s_StartTime)
    ).count();
}

CTime CTime::FromTickCount(Milli_t tickCount, bool isUTC)
{
    return CTime(tickCount, isUTC);
}

std::string CTime::ToString() const
{
    auto tm = GetTimeStruct(m_TimePoint, m_IsUTC);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << GetMillisecond()
        << (m_IsUTC ? " UTC" : " Local");
    return ss.str();
}

Milli_t CTime::GetTickCount64()
{
    return CalculateTickCount();
}

Milli_t CTime::GetElapsedTick(Milli_t tick)
{
    return GetTickCount64() - tick;
}

Milli_t CTime::GetDiffedTick(Milli_t tick)
{
    Milli_t currentTick = GetTickCount64();
    return (currentTick > tick) ? (currentTick - tick) : (tick - currentTick);
}

bool CTime::IsPast(Milli_t tick)
{
    return GetTickCount64() > tick;
}

bool CTime::IsFuture(Milli_t tick)
{
    return GetTickCount64() <= tick;
}

CTime CTime::ToUTC(const CTime& localTime)
{
    if (localTime.IsUTC())
    {
        return localTime;
    }

    CTime utcTime(true);
    utcTime.m_TimePoint = localTime.m_TimePoint;
    return utcTime;
}

CTime CTime::ToLocal(const CTime& utcTime)
{
    if (!utcTime.IsUTC()) return utcTime;
    CTime localTime(false);
    localTime.m_TimePoint = utcTime.m_TimePoint;
    return localTime;
}

Milli_t CTime::CalculateTickCount()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - s_StartTime
    ).count();
}

std::tm CTime::GetTimeStruct(const TimePoint& tp, bool isUTC)
{
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm tm_result;
    if (isUTC) gmtime_s(&tm_result, &tt);
    else localtime_s(&tm_result, &tt);
    return tm_result;
}

TimePoint CTime::FromTimeStruct(const std::tm& tm, bool isUTC)
{
    std::time_t tt;
    if (isUTC)
    {
        tt = _mkgmtime(const_cast<std::tm*>(&tm));
    }
    else
    {
        tt = mktime(const_cast<std::tm*>(&tm));
    }

    return std::chrono::system_clock::from_time_t(tt);
}