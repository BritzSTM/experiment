/*
    https://www.algospot.com/judge/problem/read/ALLERGY

    1. 무조건 모든 음식을 다 만들어보는 탐색은 별로 좋은 선택이 아니다
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <algorithm>


using namespace std;

unordered_map<string, int> peopleMap;
vector<int> food[50];
vector<int> like[50];
int g_people{ 0 };
int g_food{ 0 };

inline void clearAll()
{
    peopleMap.clear();

    for (auto& f : food)
    {
        f.clear();
    }

    for (auto& l : like)
    {
        l.clear();
    }
}

void calFoodCount(vector<int>& eatChecker, int& minFoodCnt, const int currFoodCnt)
{
    if (currFoodCnt >= minFoodCnt)
    {
        return;
    }

    // 모두 다 찾은경우. 최종 선택된 음식의 수를 갱신한다
    if (all_of(begin(eatChecker), end(eatChecker), [](int v) { return (0 < v); }))
    {
        minFoodCnt = min(minFoodCnt, currFoodCnt);
        return;
    }

    // 못 먹은 사람을 선출한다
    auto hungryIter = find(eatChecker.begin(), eatChecker.end(), 0);
    if (hungryIter == eatChecker.end())
    {
        return;
    }

    // 못먹은 사람이 먹을 수 있는 음식을 만들어 반복한다
    // 해당음식을 좋아하는 사람도 추가 해야함
    int idx = distance(eatChecker.begin(), hungryIter);
    for (const auto& selectedFood : like[idx])
    {
        for (const auto& people : food[selectedFood])
        {
            ++eatChecker[people];
        }

        calFoodCount(eatChecker, minFoodCnt, currFoodCnt + 1);

        for (const auto& people : food[selectedFood])
        {
            --eatChecker[people];
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);

    vector<int> res;
    int testCase{ 0 };
    cin >> testCase;

    while (testCase--)
    {
        cin >> g_people >> g_food;

        peopleMap.reserve(g_people);
        for (int n{ 0 }; n < g_people; ++n)
        {
            string name;
            cin >> name;
            peopleMap[name] = n;
        }

        for (int m{ 0 }; m < g_food; ++m)
        {
            //사람수
            int eatPeople{ 0 };
            cin >> eatPeople;

            while (eatPeople--)
            {
                string name;
                cin >> name;

                food[m].push_back(peopleMap[name]);
                like[peopleMap[name]].push_back(m);
            }
        }

        vector<int> eatChecker(g_people, 0);
        int minFood = g_food;

        calFoodCount(eatChecker, minFood, 0);
        res.push_back(minFood);

        clearAll();
    }

    copy(begin(res), end(res), ostream_iterator<int>{cout, "\n"});
    
    return 0;
}