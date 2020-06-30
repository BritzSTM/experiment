/*
    https://www.acmicpc.net/problem/9095
*/
#include <iostream>
#include <vector>

using namespace std;

int CalCombination(const int target, const int now)
{
    if (target == now)
    {
        return 1;
    }

    int res{ 0 };
    for (int i{ 1 }; i <= 3; ++i)
    {
        int next = now + i;

        if (next <= target)
        {
            res += CalCombination(target, now + i);
        }
        else
        {
            break;
        }
    }

    return res;
}

int main(void)
{
    ios::sync_with_stdio(false);

    int testCase{ 0 };
    cin >> testCase;

    vector<int> nums;
    while (testCase--)
    {
        int n{0};
        cin >> n;

        nums.push_back(n);
    }

    for (const auto& n : nums)
    {
        cout << CalCombination(n, 0) << endl;
    }
    
    return 0;
}