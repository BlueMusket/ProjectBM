#pragma once
#include <chrono>
#include <ctime>

using Milli_t = long long;
static const Milli_t INVALID_TIME = -1;
static const Milli_t INFINITE_TIME = LLONG_MAX;

namespace Time
{
    /// <summary>
    /// ���� �ð��� �и��� ������ ��ȯ
    /// </summary>
    /// <returns>���� �ð��� ��Ÿ���� �и���</returns>
    const Milli_t GetCurrentMilliTick();

    /// <summary>
    /// �־��� �и��� �ð��� ���� �ð��� ���� ���� ��ȯ
    /// </summary>
    /// <param name="tick"> �и��� ������ �ð� �� </param>
    /// <returns>���� �ð��� tick ���� ���� �и��� �ð�</returns>
    Milli_t GetElapsedTick(Milli_t tick);

    /// <summary>
    /// �־��� �и��� �ð��� ���� �ð��� ���̸� ��ȯ
    /// </summary>
    /// <param name="tick"> ���� �и��� ������ �ð� �� </param>
    /// <returns>���� �ð��� tick �ð��� ���̸� ��Ÿ���� �и��� ��</returns>
    Milli_t GetDiffedTick(Milli_t tick);

    /// <summary>
    /// �־��� �ð��� ���� �ð����� �������� Ȯ��
    /// </summary>
    /// <param name="tick"> Ȯ���� �и��� ������ �ð� �� </param>
    /// <returns>���� �ð����� �����̸� true, �ƴϸ� false</returns>
    bool IsPast(Milli_t tick);

    /// <summary>
    /// �־��� �ð��� ���� �ð����� �̷����� Ȯ��
    /// </summary>
    /// <param name="tick"> Ȯ���� �и��� ������ �ð� �� </param>
    /// <returns>���� �ð����� �̷��̸� true, �ƴϸ� false</returns>
    bool IsFeature(Milli_t tick);
}
