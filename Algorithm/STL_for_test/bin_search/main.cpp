#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>


using namespace std;

bool search_linear(const int val, const vector<int>& arr)
{
    for (const auto& elem : arr)
    {
        if (elem == val)
            return true;
    }

    return false;
}

bool search_binary(const int val, const vector<int>& arr)
{
    auto first{ arr.cbegin() };
    auto last{ arr.cend() };

    while (true)
    {
        auto range_len{ distance(first, last) };
        auto mid_iter{ first + floor(range_len / 2) };

        if (*mid_iter == val)
            return true;
        else if (*mid_iter < val)
        {
            first = mid_iter;
        }
        else
        {
            last = mid_iter;
        }

        if (range_len == 1)
            return false;
    }

    return false;
}

vector<int> CreateRandomVals(const int n)
{
    vector<int> res;
    res.reserve(n);

    random_device rd;
    mt19937 device(rd());
    uniform_int_distribution<int> range(0, n);

    for (auto i{ 0 }; i < n; ++i)
        res.push_back(range(device));

    sort(begin(res), end(res));

    return res;
}

int main(void)
{
    const auto randomVals{ CreateRandomVals(5'000'000) };
    const int target{ 246'747 };

    cout << "Search " << target << endl;

    using namespace chrono;
    cout << "binary" << endl;
    auto start{ steady_clock::now() };
    cout << boolalpha << search_binary(target, randomVals) << " ";
    auto end{ steady_clock::now() };
    cout << duration_cast<microseconds>(end - start).count() << "ms" <<endl;

    cout << "linear" << endl;
    start = steady_clock::now();
    cout << boolalpha << search_linear(target, randomVals) << " ";
    end = steady_clock::now();
    cout << duration_cast<microseconds>(end - start).count() << "ms" << endl;

    return 0;
}