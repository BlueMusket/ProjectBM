#pragma once

namespace Math
{
    /// <summary>
    /// 두 개의 값을 비교하여 더 작은 값을 반환합니다.
    /// </summary>
    /// <typeparam name="T">비교할 값의 형식입니다.</typeparam>
    /// <param name="a">비교할 첫 번째 값입니다.</param>
    /// <param name="b">비교할 두 번째 값입니다.</param>
    /// <returns>두 값 중 더 작은 값을 반환합니다.</returns>
    template <typename T>
    T Min(T a, T b) 
    {
        return (a < b) ? a : b;
    }

    /// 두 개의 값을 비교하여 더 큰 값을 반환합니다.
    /// </summary>
    /// <typeparam name="T">비교할 값의 형식입니다.</typeparam>
    /// <param name="a">비교할 첫 번째 값입니다.</param>
    /// <param name="b">비교할 두 번째 값입니다.</param>
    /// <returns>두 값 중 더 큰 값을 반환합니다.</returns>
    template <typename T>
    T Max(T a, T b) 
    {
        return (a > b) ? a : b;
    }

}