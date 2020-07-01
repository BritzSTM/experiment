/*
    https://www.acmicpc.net/problem/1236

    시행착오
    1. 너무 어렵게 풀려고 했음. 문제를 다시 한번 보고 고민해 보자
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int kMax{ 50 };
int g_castle[kMax][kMax]{};
int g_h;
int g_w;


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> g_h >> g_w;

    vector<bool> hGuard(g_h);
    vector<bool> wGuard(g_w);

    for (int i{ 0 }; i < g_h; ++i)
    {
        for (int j{ 0 }; j < g_w; ++j)
        {
            char c;
            cin >> c;

            if (c == 'X')
            {
                hGuard[i] = true;
                wGuard[j] = true;
            }
        }   
    }

    int hGuardCnt = count(begin(hGuard), end(hGuard), false);
    int wGuardCnt = count(begin(wGuard), end(wGuard), false);

    cout << max(hGuardCnt, wGuardCnt);

    return 0;
}