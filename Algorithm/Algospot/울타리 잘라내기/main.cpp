/*
   https://www.algospot.com/judge/problem/read/FENCE
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>


using namespace std;

// [lo, hi] 구간을 나타낸다
int getMaxPanel(const vector<int>& fence, const int lo, const int hi)
{
    // 기저 하나의 판만 있을 경우
    if (lo == hi)
    {
        return fence[lo];
    }

    //좌우 분할해서 큰값을 획득
    int mid{ (lo + hi) / 2 };
    int maxLhVal = max(getMaxPanel(fence, lo, mid), getMaxPanel(fence, mid + 1, hi));

    // 양측에 걸쳐있을 경우를 계산할 것
    int loCursor{ mid };
    int hiCursor{ mid };
    int minHeight{ fence[mid] };
    int maxMVal{ fence[mid] };
    
    //항상 커서가 있는 곳은 이미 포함되어서 계산되었다는 조건이 있음
    while (loCursor > lo || hiCursor < hi)
    {
  
        int nextloCursorPanel{ -1 };
        if (loCursor > lo)
        {
            nextloCursorPanel = fence[loCursor - 1];
        }

        int nextHiCursorPanel{ -1 };
        if (hiCursor < hi)
        {
            nextHiCursorPanel = fence[hiCursor + 1];
        }

        if (nextloCursorPanel < nextHiCursorPanel)
        {
            ++hiCursor;
            minHeight = min(minHeight, fence[hiCursor]);
        }
        else
        {
            --loCursor;
            minHeight = min(minHeight, fence[loCursor]);
        }

        //좌우로 확장시 최대 값을 획득해야 한다
        int midFinalSize{ (hiCursor - loCursor + 1) * minHeight };
        maxMVal = max(maxMVal, midFinalSize);
    }

    
    return max(maxLhVal, maxMVal);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int testCase{ 0 };
    cin >> testCase;

    vector<int> res;
    while (testCase--)
    {
        int n{ 0 };
        cin >> n;

        vector<int> fence(n);
        for (auto& v : fence)
        {
            cin >> v;
        }

        res.push_back(getMaxPanel(fence, 0, fence.size() - 1));
    }

    copy(begin(res), end(res), ostream_iterator<int>{cout, "\n"});

    return 0;
}
