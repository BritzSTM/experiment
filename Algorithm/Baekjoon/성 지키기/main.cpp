#include <iostream>
#include <algorithm>

using namespace std;

constexpr int kMax{ 50 };
int g_castle[kMax][kMax]{};
int g_h;
int g_w;

bool isOutOfRange(int y, int x)
{
    return (y < 0 || y >= g_h || x < 0 || x >= g_w);
}

void fill(int y, int x, int type)
{
    //해당 지점이 정해지면 해당 행렬에 전부 type을 더 함
    g_castle[y][x] += type;

    for (int i{ x + 1 }; !isOutOfRange(y, i); ++i)
    {
        g_castle[y][i] += type;
    }

    for (int i{ x - 1 }; !isOutOfRange(y, i); --i)
    {
        g_castle[y][i] += type;
    }

    for (int j{ y - 1 }; !isOutOfRange(j, x); --j)
    {
        g_castle[j][x] += type;
    }

    for (int j{ y + 1 }; !isOutOfRange(j, x); ++j)
    {
        g_castle[j][x] += type;
    }
}

int findMinimal()
{
    // 행과 열중에 가장 비어있는 곳이 답이다.
    int wG{ 0 };

    //열중에 가장 크게 비어 있는곳을 찾는다.
    for (int j{ 0 }; j < g_w; ++j)
    {
        int tmp{ 0 };
        for (int i{ 0 }; i < g_h; ++i)
        {
            if (g_castle[i][j] == 0)
            {
                ++tmp;
            }
        }
        wG = max(tmp, wG);
    }

    int hG{ 0 };
    for (int i{ 0 }; i < g_h; ++i)
    {
        int tmp{ 0 };
        for (int j{ 0 }; j < g_w; ++j)
        {
            if (g_castle[i][j] == 0)
            {
                ++tmp;
            }
        }
        hG = max(tmp, hG);
    }

    return max(hG, wG);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> g_h >> g_w;

    for (int i{ 0 }; i < g_h; ++i)
    {
        for (int j{ 0 }; j < g_w; ++j)
        {
            char c;
            cin >> c;

            if (c == 'X')
            {
                fill(i, j, 1);
            }
        }   
    }

    cout << findMinimal() << endl;

    return 0;
}