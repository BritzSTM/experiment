#include <iostream>
#include <array>

using namespace std;

array<int, 5> g_arr{ 1, 2, 3, 4, 5 };
array<bool, 5> g_pickFlag{};
array<int, 5> g_picked{};

constexpr int g_pickCnt{2};
int g_printCnt{ 0 };

// nPk
void perm(const int n, const int k)
{
    // 기저
    if (k == 0)
    {
        for (int i{ 0 }; i < g_pickCnt; ++i)
        {
            cout << g_picked[i] << " ";
        }

        cout << endl;
        ++g_printCnt;
    }
    else
    {
        for (int i{ 0 }; i < g_pickFlag.size(); ++i)
        {
            if (!g_pickFlag[i])
            {
                g_pickFlag[i] = true;
                g_picked[k - 1] = g_arr[i];
                perm(n, k - 1);
                g_pickFlag[i] = false;
            }
        }
    }
}

int main(void)
{
    perm(g_arr.size(), g_pickCnt);
    cout << g_printCnt;

    return 0;
}