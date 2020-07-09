#include <iostream>
#include <string>
#include <chrono>
#include <type_traits>
#include <vector>

#include "bible.h"

using namespace std;

/*
   문자열 검색 api 만들기
*/

struct SearchPolicyTag {};
struct BrutePolicy : SearchPolicyTag {};
struct KMPPolicy : SearchPolicyTag {};
struct RabinCarp : SearchPolicyTag {};
struct BoyerMoore : SearchPolicyTag {};

namespace _internal
{
    template<typename _Iter>
    _Iter SearchStringWithBrute(const string pattern, _Iter first, _Iter last)
    {
        while (first != last)
        {
            int equalCnt{ 0 };
            auto srcIter{ first };
            for (const auto& c : pattern)
            {
                if (c == *srcIter)
                {
                    ++equalCnt;
                    ++srcIter;
                }
                else
                {
                    break;
                }
            }

            if (equalCnt == pattern.size())
            {
                return first;
            }
            else
            {
                ++first;
            }
        }

        return last;
    }

    // kmp에서 이동에 필요한 table을 반환
    template<typename _Iter>
    vector<int> GetKmpPi(const _Iter first, const _Iter last)
    {
        const auto diff{ last - first };
        vector<int> res(diff, 0);

        // 전달되는 문자열의 패턴을 슬라이딩 시키면서 유사도를 계산
        for (int i{ 1 }, j{ 0 }; i < diff; ++i)
        {
            while (j > 0 && *(first + i) != *(first + j))
            {
                j = res[j - 1];
            }

            if (*(first + i) == *(first + j))
            {
                res[i] = ++j;
            }
        }
        
        return res;
    }

    template<typename _Iter>
    _Iter SearchStringWithKMP(const string pattern, _Iter first, _Iter last)
    {
        // Pi 배열을 획득
        const vector<int> Pi(GetKmpPi(first, last));
    }
}

template<typename _Policy, typename _Iter>
_Iter SearchString(const string pattern, _Iter srcIter, _Iter endIter)
{
    
}

int main(void)
{
    // string src{ "DogDogDogdogDogDog" };
    // auto iter = _internal::SearchStringWithBrute("dog", begin(src), end(src));
    string s{ "ABABABAC" };
    auto res{ _internal::GetKmpPi(begin(s), end(s)) };

    return 0;
}