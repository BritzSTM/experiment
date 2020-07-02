/*
    https://www.algospot.com/judge/problem/read/JUMPGAME
*/
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

constexpr int kMaxN = 100;
int g_n;
int g_board[kMaxN][kMaxN];
constexpr int kNotFound = -1;
int g_cache[kMaxN][kMaxN];


inline void initStream()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

void fillCache(const int v)
{
    std::memset(&g_cache, v, sizeof(g_cache));
}

int jump(const int y, const int x)
{
    // 기저 사항을 처리한다
    if (y >= g_n || x >= g_n)
    {
        return 0;
    }

    if (y == g_n - 1 && x == g_n - 1)
    {
        return 1;
    }

    int& res = g_cache[y][x];
    if (res != kNotFound)
    {
        return res;
    }

    //다음 장소로 이동하고 끝까지 이동 가능하다면 흔적을 남긴다
    int jumpSize = g_board[y][x];
    res = (jump(y + jumpSize, x) || jump(y, x + jumpSize));

    return res;
}

int main(void)
{
    initStream();

    int testCase{ 0 };
    cin >> testCase;

    vector<int> res;
    res.reserve(testCase);

    while (testCase--)
    {
        cin >> g_n;
        fillCache(kNotFound);

        for (int i{ 0 }; i < g_n; ++i)
        {
            for (int j{ 0 }; j < g_n; ++j)
            {
                cin >> g_board[i][j];
            }
        }

        res.push_back(jump(0, 0));
    }

    transform(begin(res), end(res),
        ostream_iterator<string>{cout, "\n"}, 
        [](int& v)
        {
            const char* const pszText[2]{ "NO", "YES" };
            return pszText[v];
        });

    return 0;
}