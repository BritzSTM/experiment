#include <iostream>
#include <array>

using namespace std;

array<int, 11> g_datas{ 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9, 10 };
array<int, g_datas.size()> g_fenwick{};

void push_fenwick(const int index, const int value)
{
    int effectIdx{ index };

    while (effectIdx < g_fenwick.size())
    {
        g_fenwick[effectIdx] += value;
        effectIdx += (effectIdx & -effectIdx);
    }
}

int sum_fenwick(const int hi)
{
    int res{ 0 };
    int effectIdx{ hi };
    
    while (0 < effectIdx)
    {
        res += g_fenwick[effectIdx];
        effectIdx -= (effectIdx & -effectIdx);
    }

    return res;
}

int sum_fenwick(const int lo, const int hi)
{
    return sum_fenwick(hi) - sum_fenwick(lo - 1);
}

int main(void)
{
    // build 
    for (int i{ 1 }; i < g_datas.size(); ++i)
    {
        push_fenwick(i, g_datas[i]);
    }

    // sum
    cout << sum_fenwick(10) << endl;
    cout << sum_fenwick(1, 10) << endl;
    cout << sum_fenwick(1, 5) << endl;
    cout << sum_fenwick(3, 5) << endl;

    return 0;
}