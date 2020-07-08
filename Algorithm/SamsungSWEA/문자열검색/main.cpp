#include <iostream>
#include <string>
#include <chrono>
#include <type_traits>

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

    template<typename _Iter>
    _Iter SearchStringWithKMP(const string pattern, _Iter first, _Iter last)
    {

    }
}

template<typename _Policy, typename _Iter>
_Iter SearchString(const string pattern, _Iter srcIter, _Iter endIter)
{
    
}

int main(void)
{
    string src{ "DogDogDogdogDogDog" };
    auto iter = _internal::SearchStringWithBrute("dog", begin(src), end(src));
    
    return 0;
}