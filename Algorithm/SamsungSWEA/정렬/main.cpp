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
// 선택
// 삽입

int main(void)
{
    vector<int> src{ getRandomSrc(-1000, 1000, 1000) };

    vector<int> correct{ src };
    sort(begin(correct), end(correct));

    vector<int> bubble{ src };


    assert(bubble == correct);

    return 0;
}