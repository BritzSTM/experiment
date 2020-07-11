#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> getRandomSrc(const int min, const int max, const int n)
{
    random_device rd;
    mt19937 mt{ rd() };
    uniform_int_distribution<int> dist{ min, max };

    vector<int> src(n, 0);
    for (int i{ 0 }; i < n; ++i)
    {
        src[i] = dist(mt);
    }

    return std::move(src);
}

// 버블
template<typename _Iter>
void bubbleSort(const _Iter first, const  _Iter last)
{
    const auto diff{ last - first };

    for (auto i{ 0 }; i < diff; ++i)
    {
        for (auto iter{ first + 1 }; iter != (last - i); ++iter)
        {
            if (*iter < *(iter - 1))
            {
                swap(*iter, *(iter - 1));
            }
        }
    }

    return;
}

// 선택
template<typename _Iter>
void selectionSort(const _Iter first, const  _Iter last)
{
    const auto diff{ last - first };

    for (auto i{ 0 }; i < diff; ++i)
    {
        auto minIter{ first + i };
        for (auto iter{ minIter + 1}; iter != last; ++iter)
        {
            if (*iter < *minIter)
            {
                minIter = iter;
            }
        }

        swap(*(first + i), *minIter);
    }

    return;
}

// 삽입

int main(void)
{
    vector<int> src{ getRandomSrc(-10000, 10000, 1000) };

    vector<int> correct{ src };
    sort(begin(correct), end(correct));

    vector<int> bubble{ src };
    bubbleSort(begin(bubble), end(bubble));
    assert(bubble == correct);

    vector<int> selection{ src };
    selectionSort(begin(selection), end(selection));
    assert(selection == correct);

    return 0;
}