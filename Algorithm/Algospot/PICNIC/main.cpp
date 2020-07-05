/*
    https://www.algospot.com/judge/problem/read/PICNIC

    중복되는 수를 제외하기 위해 선택을 강제하는 방법을 사용함
*/
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

constexpr int kMaxPeopleCount{ 10 };
constexpr int kNotFound{ -1 };

int g_peopleCount{ 0 };
array<array<bool, kMaxPeopleCount>, kMaxPeopleCount> g_fsTable {};

int findFirstOrder(const array<bool, kMaxPeopleCount>& taken) noexcept
{
    for (int i{ 0 }; i < g_peopleCount; ++i)
    {
        if (!taken[i])
        {
            return i;
        }
    }

    return kNotFound;
}

int countingMatchPair(array<bool, kMaxPeopleCount>& taken) noexcept
{
    //순서를 강제하기 위한 순서 설정
    int pair1{ findFirstOrder(taken) };

    if (pair1 == kNotFound)
    {
        return 1;
    }

    int accRes{ 0 };

    //순서를 강제 했으므로 pair2는 pair1의 다음이다.
    for (int pair2{ pair1 + 1 }; pair2 < g_peopleCount; ++pair2)
    {
        if (!taken[pair2] && g_fsTable[pair1][pair2])
        {
            taken[pair1] = taken[pair2] = true;
            accRes += countingMatchPair(taken);
            taken[pair1] = taken[pair2] = false;
        }
    }

    return accRes;
}


int main()
{
    int testCase{0};
    cin >> testCase;

    vector<int> resVec;
    while(testCase--)
    {
        //make fsTable
        int pairCount;
        cin >> g_peopleCount >> pairCount;

        for (int j{ 0 }; j < pairCount; ++j)
        {
            int p1, p2;
            cin >> p1 >> p2;

            g_fsTable[p1][p2] = g_fsTable[p2][p1] = true;
        }

        //findPairCount
        array<bool, kMaxPeopleCount> taken{};
        resVec.push_back(countingMatchPair(taken));

        //table clear
        g_fsTable = {};
    }

    copy(begin(resVec), end(resVec), ostream_iterator<int>{cout, "\n"});

    return 0;
}