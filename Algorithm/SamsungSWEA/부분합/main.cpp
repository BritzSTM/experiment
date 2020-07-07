/*
    SW 문제해결 Self Study Book Ⅰ

    한계점 
    비트마스크 연산을 이용했기 때문에 자료형의 비트수의 갯수가 요소의 제한점이 된다 
*/
#include <iostream>
#include <array>

using namespace std;

constexpr int kElemCnt{ 5 };
array<int, kElemCnt> g_arr{ -7, -3, -2, 5, 8 };

int main(void)
{
    const int testCase{ 0x01 << kElemCnt };
    bool found{ false };
    
    // 1부터 시작하는 이유는 0은 공집합이기 때문
    for (int i{ 1 }; i < testCase; ++i)
    {
        int sum{ 0 };
        for (int j{ 0 }; j < kElemCnt; ++j)
        {
            const int setElem{ 0x01 << j };
            if (i & setElem)
            {
                sum += g_arr[j];
            }
        }

        if (sum == 0)
        {
            found = true;
        }
    }

    cout << boolalpha << found << endl;

    return 0;
}