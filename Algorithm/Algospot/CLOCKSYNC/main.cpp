/*
    https://www.algospot.com/judge/problem/read/CLOCKSYNC
*/
#include <iostream>
#include <array>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

using namespace std;

constexpr int kClockCount = 16;
constexpr int kSwitchCount = 10;
constexpr int kTtargetClock = 12;
constexpr int kNotFound = 999'999'999;

struct SClock
{
    int time;

    void nextTime()
    {
        //12, 3, 6, 9
        time += 3;

        if (time > 12)
        {
            time = 3;
        }
    }
};

array<SClock, kClockCount> g_clocks;
array<vector<int>, kSwitchCount> g_clockConn
{
    {{0, 1, 2},
    {3, 7, 9, 11},
    {4, 10, 14, 15},
    {0, 4, 5, 6, 7},
    {6, 7, 8, 10, 12},
    {0, 2, 14, 15},
    {3, 14, 15},
    {4, 5, 7, 14, 15},
    {1, 2, 3, 4, 5},
    {3, 4, 5, 9, 13}}
};

int pushSwitch(int currSw)
{
    //기저
    if (kSwitchCount == currSw)
    {
        if (all_of(begin(g_clocks), end(g_clocks), [](const auto& clock) { return clock.time == kTtargetClock;}))
        {
            return 0;
        }
        else
        {
            return kNotFound;
        }
    }

    int res{ kNotFound };
    for (int i{ 0 }; i < 4; ++i)
    {
        res = min(res, i + pushSwitch(currSw + 1));

        for (auto& line : g_clockConn[currSw])
        {
            g_clocks[line].nextTime();
        }
    }

    return res;
}

int main(void)
{
    //12 6 6 6 6 6 12 12 12 12 12 12 12 12 12 12

    int testCase{ 0 };
    cin >> testCase;

    vector<int> res;
    while (testCase--)
    {
        for (int i{ 0 }; i < kClockCount; ++i)
        {
            cin >> g_clocks[i].time;
        }

        res.push_back(pushSwitch(0));
    }

    copy(begin(res), end(res), ostream_iterator<int>{cout, "\n"});

    return 0;
}