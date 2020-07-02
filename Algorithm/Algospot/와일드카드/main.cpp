#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

//멈춘 위치가 틀린 위치
int _getMissMatchPos(const string& pattern, const string& str)
{
    int pos{ 0 };
    while (pos < pattern.size() && pos < str.size())
    {
        if (!(pattern[pos] == '?' || pattern[pos] == str[pos]))
        {
            break;
        }

        ++pos;
    }

    return pos;
}

bool isMatch(string pattern, string str)
{
    // 일치하는 곳까지 패턴을 분리한다
    int pos = _getMissMatchPos(pattern, str);
    
    // 패턴이 다 완료되었는지 확인
    if (pos == pattern.size() && pos == str.size())
    {
        return true;
    }

    // 검사를 멈춘 위치가 *인지확인
    if (pattern[pos] == '*')
    {
        for (int skip{ 0 }; pos + skip <= str.size(); ++skip)
        {
            if (isMatch(pattern.substr(pos + 1), str.substr(pos + skip)))
            {
                return true;
            }
        }
    }

    //위 조건을 만족 못했다면 불일치
    return false;    
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int testCase{ 0 };
    cin >> testCase;

    vector<string> res;
    res.reserve(testCase);

    while (testCase--)
    {
        string p;
        cin >> p;

        int fileCnt{ 0 };
        cin >> fileCnt;
        vector<string> files(fileCnt);

        for (int i{ 0 }; i < fileCnt; ++i)
        {
            cin >> files[i];
        }

        for (auto& f : files)
        {
            if (isMatch(p, f))
            {
                res.push_back(f);
            }
        }
    }

    sort(begin(res), end(res));
    copy(begin(res), end(res), ostream_iterator<string>{cout, "\n"});

    return 0;
}