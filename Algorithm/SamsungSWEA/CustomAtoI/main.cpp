/*
    최대한 가독성을 높이기 위해 조건 인라인 함수를 작성해 적용해 봄
*/
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// 1 or -1을 반환
inline int getSign(const char c) noexcept
{
    return { (c == '-') ? -1 : 1 };
}

inline bool isNum(const char c) noexcept
{
    return { c >= '0' && c <= '9' };
}

inline bool isSign(const char c) noexcept
{
    return { c == '+' || c == '-' };
}

inline int toInt(const char c) noexcept
{
    return { isNum(c) ? (c - '0') : 0 };
}

/*
    부호를 포함할 수도 있는 문자열을 전달 받음
    최대한 변환 가능한 문자열을 변환
*/
int customAtoI(const string s, int* const pOutPos = nullptr)
{
    if (pOutPos != nullptr)
    {
        *pOutPos = -1;
    }

    if (s.size() == 0)
    {
        return 0;
    }

    int sign{ 1 };
    int convInt{ 0 };
    int lastPos{ 1 };

    //부호가 있을 수 있는 0번 지점만 따로 처리
    if (isSign(s[0]))
    {
        sign = getSign(s[0]);
    }
    else if (isNum(s[0]))
    {
        convInt += toInt(s[0]);
    }
    else
    {
        return 0;
    }

    while (lastPos < s.size())
    {
        if (isNum(s[lastPos]))
        {
            convInt *= 10;
            convInt += toInt(s[lastPos]);

            ++lastPos;
            continue;
        }

        break;
    }

    if (pOutPos != nullptr)
    {
        *pOutPos = lastPos - 1;
    }

    return { sign * convInt };
}

int main(void)
{
    int pos{0};

    assert(customAtoI("", &pos) == 0 && pos == -1);
    assert(customAtoI("+", &pos) == 0 && pos == 0);
    assert(customAtoI("+123", &pos) == 123 && pos ==  3);
    assert(customAtoI("-123", &pos) == -123 && pos == 3);
    assert(customAtoI("123a5", &pos) == 123 && pos == 2);
    assert(customAtoI("+1234a4", &pos) == 1234 && pos == 4);

    return 0;
}