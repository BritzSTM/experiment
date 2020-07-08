#include <iostream>

using namespace std;

constexpr int kMax = 5;
int g_arr[kMax][kMax]
{
     1,  2,  3,  4,  5,
     6,  7,  8,  9, 10,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20,
    21, 22, 23, 24, 25
};

// 이동을 위한 dy, dx 값
int g_offset[1][2]{ -1, 1 };

// 이 함수는 kMax에 종속
inline bool isOutOfRange(int y, int x)
{
    return (y < 0 || y >= kMax || x < 0 || x >= kMax);
}

int main(void)
{
    const int halfIdx{ kMax - 1 };
    int lineFeedCnt{ 0 };

    for (int i{ 0 }; i < (kMax*2) - 1; ++i)
    {
        //반복문 중간지점 +1 부터 dy의 증가가 아닌 dx가 x(1)부터 증가되어야 한다.
        int dy{ i <= halfIdx ? i : halfIdx };
        int dx{ i > halfIdx ? i - kMax + 1 : 0};

        while (!isOutOfRange(dy, dx))
        {
            cout << g_arr[dy][dx] << " ";

            dy += g_offset[0][0];
            dx += g_offset[0][1];
            
            if (++lineFeedCnt == kMax)
            {
                cout << endl;
                lineFeedCnt = 0;
            }
        }
    }

    return 0;
}