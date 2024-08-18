#include "Time.h"

namespace Tick
{
    /// <summary>
    /// 현재 시간을 밀리초 단위로 반환
    /// </summary>
    /// <returns>현재 시간을 나타내는 밀리초</returns>
    const Milli_t GetCurrentMilliTick()
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::milliseconds milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return milliseconds_since_epoch.count();
    }

    /// <summary>
    /// 주어진 밀리초 시간에 현재 시간을 더한 값을 반환
    /// </summary>
    /// <param name="tick"> 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간에 tick 값을 더한 밀리초 시간</returns>
    Milli_t GetElapsedTick(Milli_t tick)
    {
        return GetCurrentMilliTick() + tick;
    }

    /// <summary>
    /// 주어진 밀리초 시간과 현재 시간의 차이를 반환
    /// </summary>
    /// <param name="tick"> 비교할 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간과 tick 시간의 차이를 나타내는 밀리초 값</returns>
    Milli_t GetDiffedTick(Milli_t tick)
    {
        Milli_t now = GetCurrentMilliTick();
        return now < tick ? tick - now : now - tick;
    }

    /// <summary>
    /// 주어진 시간이 현재 시간보다 과거인지 확인
    /// </summary>
    /// <param name="tick"> 확인할 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간보다 과거이면 true, 아니면 false</returns>
    bool IsPast(Milli_t tick)
    {
        return GetCurrentMilliTick() > tick;
    }

    /// <summary>
    /// 주어진 시간이 현재 시간보다 미래인지 확인
    /// </summary>
    /// <param name="tick"> 확인할 밀리초 단위의 시간 값 </param>
    /// <returns>현재 시간보다 미래이면 true, 아니면 false</returns>
    bool IsFeature(Milli_t tick)
    {
        return GetCurrentMilliTick() <= tick;
    }
}


ULONGLONG CTime::SystemTimeToULONGLONG(const SYSTEMTIME& st) 
{
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    return (static_cast<ULONGLONG>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
}

void CTime::ULONGLONGToSystemTime(ULONGLONG time, SYSTEMTIME& st) 
{
    FILETIME ft;
    ft.dwLowDateTime = static_cast<DWORD>(time & 0xFFFFFFFF);
    ft.dwHighDateTime = static_cast<DWORD>(time >> 32);
    FileTimeToSystemTime(&ft, &st);
}

void CTime::NormalizeTime() 
{
    SYSTEMTIME st;
    ULONGLONGToSystemTime(m_time, st);
    m_time = SystemTimeToULONGLONG(st);
}

ULONGLONG CTime::GetSystemStartTime() 
{
    static ULONGLONG systemStartTime = 0;

    if (0 == systemStartTime)
    {
        FILETIME ft;
        ULONGLONG now = GetTickCount64();
        GetSystemTimeAsFileTime(&ft);
        ULONGLONG current = (static_cast<ULONGLONG>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
        systemStartTime = current - (now * 10000ULL);
    }

    return systemStartTime;
}

CTime::CTime(bool isUTC) 
    : m_isUTC(isUTC) 
{
    SYSTEMTIME st;
    if (m_isUTC) 
    {
        GetSystemTime(&st);
    }
    else 
    {
        GetLocalTime(&st);
    }

    m_time = SystemTimeToULONGLONG(st);
}

CTime::CTime(const SYSTEMTIME& st, bool isUTC)
    : m_time(SystemTimeToULONGLONG(st))
    , m_isUTC(isUTC)
{}

bool CTime::IsUTC() const 
{
    return m_isUTC;
}

void CTime::SetToUTC() 
{
    if (!m_isUTC) 
    {
        SYSTEMTIME st, utc;
        ULONGLONGToSystemTime(m_time, st);
        TzSpecificLocalTimeToSystemTime(NULL, &st, &utc);
        m_time = SystemTimeToULONGLONG(utc);
        m_isUTC = true;
    }
}

void CTime::SetToLocal() 
{
    if (m_isUTC) 
    {
        SYSTEMTIME st, local;
        ULONGLONGToSystemTime(m_time, st);
        SystemTimeToTzSpecificLocalTime(NULL, &st, &local);
        m_time = SystemTimeToULONGLONG(local);
        m_isUTC = false;
    }
}

void CTime::AddYears(int years) 
{
    SYSTEMTIME st;
    ULONGLONGToSystemTime(m_time, st);
    st.wYear += years;
    m_time = SystemTimeToULONGLONG(st);
    NormalizeTime();
}

void CTime::AddMonths(int months) 
{
    SYSTEMTIME st;
    ULONGLONGToSystemTime(m_time, st);
    int totalMonths = st.wMonth + months - 1;
    st.wYear += totalMonths / 12;
    st.wMonth = (totalMonths % 12) + 1;
    m_time = SystemTimeToULONGLONG(st);
    NormalizeTime();
}

void CTime::AddDays(int days) 
{
    m_time += static_cast<ULONGLONG>(days) * 24LL * 60LL * 60LL * 10000000LL;
}

void CTime::AddHours(int hours) 
{
    m_time += static_cast<ULONGLONG>(hours) * 60LL * 60LL * 10000000LL;
}

void CTime::AddMinutes(int minutes) 
{
    m_time += static_cast<ULONGLONG>(minutes) * 60LL * 10000000LL;
}

void CTime::AddSeconds(int seconds) 
{
    m_time += static_cast<ULONGLONG>(seconds) * 10000000LL;
}

void CTime::AddMilliseconds(int milliseconds) 
{
    m_time += static_cast<ULONGLONG>(milliseconds) * 10000LL;
}

std::string CTime::ToString(const std::string& format) const 
{
    SYSTEMTIME st;
    ULONGLONGToSystemTime(m_time, st);

    std::ostringstream oss;
    oss << std::setfill('0');

    for (size_t i = 0; i < format.length(); ++i) 
    {
        if (format[i] == '%') 
        {
            switch (format[++i]) 
            {
            case 'Y': oss << std::setw(4) << st.wYear; break;
            case 'm': oss << std::setw(2) << st.wMonth; break;
            case 'd': oss << std::setw(2) << st.wDay; break;
            case 'H': oss << std::setw(2) << st.wHour; break;
            case 'M': oss << std::setw(2) << st.wMinute; break;
            case 'S': oss << std::setw(2) << st.wSecond; break;
            case 'f': oss << std::setw(3) << st.wMilliseconds; break;
            case 'z': oss << (m_isUTC ? "UTC" : "Local"); break;
            default: oss << '%' << format[i]; break;
            }
        }
        else 
        {
            oss << format[i];
        }
    }

    return oss.str();
}

ULONGLONG CTime::ToULONGLONG() const 
{
    return m_time;
}

CTime CTime::FromULONGLONG(ULONGLONG value, bool isUTC) 
{
    CTime time;
    time.m_time = value;
    time.m_isUTC = isUTC;
    return time;
}

CTime CTime::FromTickCount64(bool asUTC) 
{
    ULONGLONG tickCount = GetTickCount64();
    ULONGLONG fileTime = GetSystemStartTime() + (tickCount * 10000ULL);

    CTime time(true);  // Create as UTC
    time.m_time = fileTime;

    if (!asUTC) 
    {
        time.SetToLocal();
    }

    return time;
}

ULONGLONG CTime::ToTickCount64() const 
{
    CTime utcTime = *this;
    if (!m_isUTC) 
    {
        utcTime.SetToUTC();
    }

    ULONGLONG systemStartTime = GetSystemStartTime();
    return (utcTime.m_time - systemStartTime) / 10000ULL;
}

//사용 예제
 
//// Get current time
//CTime currentTime(true); // true for UTC
//printTime(currentTime, "Current UTC time");
//
//// Convert to local time
//CTime localTime = currentTime;
//localTime.SetToLocal();
//printTime(localTime, "Current local time");
//
//// Get tick count
//ULONGLONG tickCount = currentTime.ToTickCount64();
//std::cout << "Tick count: " << tickCount << std::endl;
//
//// Convert tick count back to CTime
//CTime timeFromTick = CTime::FromTickCount64(true); // true for UTC
//printTime(timeFromTick, "Time from tick (UTC)");
//
//// Convert to ULONGLONG and back
//ULONGLONG timeValue = currentTime.ToULONGLONG();
//std::cout << "Time as ULONGLONG: " << timeValue << std::endl;
//
//CTime timeFromULONGLONG = CTime::FromULONGLONG(timeValue, true); // true for UTC
//printTime(timeFromULONGLONG, "Time from ULONGLONG");
//
//// Demonstrate time arithmetic
//CTime futureTime = currentTime;
//futureTime.AddDays(7);
//futureTime.AddHours(3);
//futureTime.AddMinutes(30);
//printTime(futureTime, "Time 7 days, 3 hours, and 30 minutes from now");
//
//Current UTC time : 2024 - 08 - 18 12:34 : 56.789 UTC
//Current local time : 2024 - 08 - 18 21:34 : 56.789 Local
//Tick count : 2345678901234
//Time from tick(UTC) : 2024 - 08 - 18 12:34 : 56.789 UTC
//Time as ULONGLONG : 133483697123456789
//Time from ULONGLONG : 2024 - 08 - 18 12:34 : 56.789 UTC
//Time 7 days, 3 hours, and 30 minutes from now : 2024 - 08 - 25 16:04 : 56.789 UTC