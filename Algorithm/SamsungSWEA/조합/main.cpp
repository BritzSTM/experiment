#include <iostream>
#include <array>

using namespace std;

array<int, 10> g_arr{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
array<int, 3> g_picked{};

void comb(const int n, const int r)
{
    if (r == 0)
    {
        for (int i{ 0 }; i < g_picked.size(); ++i)
        {
            cout << g_picked[i] << " ";
        }

        cout << endl;
    }
    else if (n < r)
    {
        return;
    }
    else
    {
        g_picked[r - 1] = g_arr[n - 1];
        comb(n - 1, r - 1);
        comb(n - 1, r);
    }
}

int main(void)
{
    comb(5, 3);
    return 0;
}