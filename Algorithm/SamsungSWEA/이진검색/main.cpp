/*
    착오

    구간성격을 섞어 쓰지 말자. 섞어 쓴다면 경계처리가 혼란스러워짐. [], [)
    랜덤접근 반복자라는 사전조건을 설정하여 작성함
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

// 반복문형
template<typename _Iter>
bool binarySearchLoop(_Iter bIter, _Iter eIter, const int findVal)
{
    for (auto diff{ eIter - bIter }; diff >= 2; diff = eIter - bIter)
    {
        const auto midIter{ bIter + (diff / 2) };

        if (findVal == *midIter)
        {
            return true;
        }

        if (findVal < *midIter)
        {
            eIter = midIter;
            continue;
        }

        const auto newBIter{ midIter + 1 };
        if (findVal > * midIter && newBIter != eIter)
        {
            bIter = newBIter;
            continue;
        }

        // 여기까지 왔으면 경계면을 벗어나는 것
        break;
    }

    return (*bIter == findVal);
}

// [bIter, eIter). 알고리즘 연습이기 때문에 iter type 검사 안함
template<typename _Iter>
bool binarySearchRcsv(const _Iter bIter, const _Iter eIter, const int findVal)
{
    const auto diff{ eIter - bIter };
    
    // 기저
    if (diff == 1)
    {
        return (*bIter == findVal);
    }

    const auto midIter{ bIter + (diff / 2) };
    if (*midIter == findVal)
    {
        return true;
    }

    if (findVal < *midIter)
    {
        return binarySearchRcsv(bIter, midIter, findVal);
    }
    
    const auto newBiter = (midIter + 1);
    if (findVal > *midIter && newBiter != eIter)
    {
        return binarySearchRcsv(newBiter, eIter, findVal);
    }

    return false;
}

template<typename _Container, typename _Fn>
void binarySearchTest(_Container&& nums, _Fn&& fn)
{
    assert(fn(begin(nums), end(nums), -300) == false);
    assert(fn(begin(nums), end(nums), -10) == false);
    assert(fn(begin(nums), end(nums), 54) == true);
    assert(fn(begin(nums), end(nums), 554) == true);
    assert(fn(begin(nums), end(nums), 691) == true);
    assert(fn(begin(nums), end(nums), 999) == true);
    assert(fn(begin(nums), end(nums), 1000) == true);
    assert(fn(begin(nums), end(nums), 1001) == false);
    assert(fn(begin(nums), end(nums), 6520) == false);
}

int main(void)
{   
    vector<int> nums(1000);
    iota(begin(nums), end(nums), 1);

    binarySearchTest(nums, binarySearchRcsv<vector<int>::iterator>);
    binarySearchTest(nums, binarySearchLoop<vector<int>::iterator>);

    return 0;
}