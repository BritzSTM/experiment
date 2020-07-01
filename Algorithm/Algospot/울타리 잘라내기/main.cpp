#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>


using namespace std;


// [lo, hi] 구간을 나타낸다
int getMaxPanel(const vector<int>& fence, const int lo, const int hi)
{
    // 기저 하나의 판만 있을 경우
    if (lo == hi)
    {
        return fence[lo];
    }

    int mid{ (lo + hi) / 2 };
    int maxVal = max(getMaxPanel(fence, lo, mid), getMaxPanel(fence, mid + 1, hi));

    // 양측에 걸쳐있을 경우를 계산할 것
    int loCursor{ mid };
    int hiCursor{ mid };
    int minHeight{ numeric_limits<int>::max() };
    
    while (loCursor > lo || hiCursor < hi)
    {
        //좌우 다음 번것이 큰것을 선택한다
        int nextloCursorPanel{ -1 };
        int nextloCursor = loCursor - 1;

        if (nextloCursor > -1 && nextloCursor >= lo)
        {
            nextloCursorPanel = fence[nextloCursor];
        }

        int nextHiCursorPanel{ -1 };
        int nextHiCursor = hiCursor - 1;

        if (nextHiCursor < fence.size() && nextHiCursor <= hi)
        {
            nextHiCursorPanel = fence[nextHiCursor];
        }

        if (nextloCursorPanel == -1 && nextHiCursorPanel == -1)
        {
            break;
        }
       
        if (nextloCursorPanel < nextHiCursorPanel)
        {
            hiCursor = nextHiCursor;
            minHeight = min(minHeight, fence[hiCursor]);
        }
        else
        {
            loCursor = nextloCursor;
            minHeight = min(minHeight, fence[loCursor]);
        }
    }

    int midFinalSize{ (hiCursor - loCursor) * minHeight };
    return max(maxVal, midFinalSize);
}

int main(void)
{
    vector<int> testCase{ 7, 1, 5, 9, 6, 7, 3 };

    cout << getMaxPanel(testCase, 0, testCase.size() - 1);
}
