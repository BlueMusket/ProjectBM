#pragma once
#include <chrono>

using Milli_t = long long;
using TimePoint = std::chrono::system_clock::time_point;
static const Milli_t INVALID_TIME = -1;
static const Milli_t INFINITE_TIME = LLONG_MAX;

class CTime
{
public:
    // Constructors
    CTime(bool isUTC = false);
    CTime(int year, int month, int day, int hour, int minute, int second, int millisecond, bool isUTC = false);
    explicit CTime(Milli_t tickCount, bool isUTC = false);

    // Get functions
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;
    int GetMillisecond() const;
    bool IsUTC() const;
    const TimePoint& GetTimePoint() const;

    // Add functions
    void AddYears(int years);
    void AddMonths(int months);
    void AddDays(int days);
    void AddHours(int hours);
    void AddMinutes(int minutes);
    void AddSeconds(int seconds);
    void AddMilliseconds(int milliseconds);

    // Conversion functions
    static Milli_t ToTickCount(CTime& time);
    static CTime FromTickCount(Milli_t tickCount, bool isUTC = false);

    // Utility functions
    std::string ToString() const;

    // Static utility functions
    static Milli_t GetTickCount64();
    static Milli_t GetElapsedTick(Milli_t tick);
    static Milli_t GetDiffedTick(Milli_t tick);
    static bool IsPast(Milli_t tick);
    static bool IsFuture(Milli_t tick);

    // Time zone conversion functions
    static CTime ToUTC(const CTime& localTime);
    static CTime ToLocal(const CTime& utcTime);

private:
    TimePoint m_TimePoint;
    bool m_IsUTC;

    static const std::chrono::steady_clock::time_point s_StartTime;
    static Milli_t CalculateTickCount();
    static std::tm GetTimeStruct(const TimePoint& tp, bool isUTC);
    static TimePoint FromTimeStruct(const std::tm& tm, bool isUTC);
};

// 예제
//
//// 1. 현재 시간으로 CTime 객체 생성
//CTime now;
//std::cout << "1. Current time: " << now.ToString() << std::endl;
//
//// 3. UTC를 로컬 시간으로 변환
//CTime localTime = CTime::ToUTC(now);
//std::cout << "3. Converted to local time: " << localTime.ToString() << std::endl;
//
//// 4. 시간 요소 가져오기
//std::cout << "4. Time components of local time:" << std::endl;
//std::cout << "   Year: " << localTime.GetYear() << std::endl;
//std::cout << "   Month: " << localTime.GetMonth() << std::endl;
//std::cout << "   Day: " << localTime.GetDay() << std::endl;
//std::cout << "   Hour: " << localTime.GetHour() << std::endl;
//std::cout << "   Minute: " << localTime.GetMinute() << std::endl;
//std::cout << "   Second: " << localTime.GetSecond() << std::endl;
//std::cout << "   Millisecond: " << localTime.GetMillisecond() << std::endl;
//
//// 5. 시간 더하기
//localTime.AddDays(1);
//localTime.AddHours(2);
//localTime.AddMinutes(30);
//std::cout << "5. After adding 1 day, 2 hours, and 30 minutes: " << localTime.ToString() << std::endl;
//
//// 6. TickCount 사용
//CTime::Milli_t startTick = CTime::GetTickCount64();
//std::this_thread::sleep_for(std::chrono::seconds(2));
//CTime::Milli_t endTick = CTime::GetTickCount64();
//
//std::cout << "6. Start TickCount: " << startTick << std::endl;
//std::cout << "   End TickCount: " << endTick << std::endl;
//std::cout << "   Elapsed time: " << CTime::GetElapsedTick(startTick) << " ms" << std::endl;
//
//// 7. TickCount와 CTime 변환
//CTime timeFromTick = CTime::FromTickCount(startTick);
//std::cout << "7. Time from start TickCount: " << timeFromTick.ToString() << std::endl;
//
//CTime::Milli_t tickFromTime = timeFromTick.ToTickCount();
//std::cout << "   TickCount from time: " << tickFromTime << std::endl;
//std::cout << "   Are TickCounts equal? " << (startTick == tickFromTime ? "Yes" : "No") << std::endl;
//
//// 8. 과거와 미래 시간 비교
//CTime::Milli_t futureTick = endTick + 5000;  // 5초 후
//std::cout << "8. Is end time in the past? " << (CTime::IsPast(endTick) ? "Yes" : "No") << std::endl;
//std::cout << "   Is future time in the future? " << (CTime::IsFuture(futureTick) ? "Yes" : "No") << std::endl;
//
//
//1. Current time : 2024 - 08 - 18 17:56 : 34.759 Local
//3. Converted to local time : 2024 - 08 - 18 08:56 : 34.759 UTC
//4. Time components of local time :
//Year: 2024
//Month : 8
//Day : 18
//Hour : 8
//Minute : 56
//Second : 34
//Millisecond : 759
//5. After adding 1 day, 2 hours, and 30 minutes : 2024 - 08 - 19 11:26 : 34.759 UTC
//6. Start TickCount : 51
//End TickCount : 2060
//Elapsed time : 2011 ms
//7. Time from start TickCount : 2024 - 08 - 18 17:56 : 34.763 Local
//TickCount from time : 51
//Are TickCounts equal ? Yes
//8. Is end time in the past ? Yes
//Is future time in the future ? Yes