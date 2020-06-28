/*
    https://algospot.com/judge/problem/read/XHAENEUNG
    
    시행착오
    1. algospot에서 사용하는 컴파일러에서는 auto 추론이 실패했었음
*/
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <cassert>


using namespace std;

constexpr int kNumTextCount = 11;
unordered_map<size_t, int> g_numPairs{ kNumTextCount }; //key = string hash, value = number

inline void fflushCin()
{
    cin.ignore();
    cin.clear();
}

inline int calHash(const string src)
{
    string s{ src };
    sort(s.begin(), s.end());

    return hash<string>{}(s);
}

void preprocess()
{
    using rawNumPair = pair<const char* const, int>;

    static const array<rawNumPair, kNumTextCount> pszNumTexts = {
        {{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}}
    };

    for (auto& pair : pszNumTexts)
    {
        auto hashVal = calHash(pair.first);
        g_numPairs[hashVal] = pair.second;
    }
}

inline bool isCorrect(int cal, int answer) noexcept
{
    return (0 <=  answer && 10 >= answer && cal == answer);
}

inline void removeWhitespace(string& s) noexcept
{
    auto iter = remove(s.begin(), s.end(), ' ');
    s.erase(iter, s.end());
}

int calValueWithOperator(int lhs, int rhs, char op)
{
    int res{ 0 };

    switch (op)
    {
    case '+':
        res = lhs + rhs;
        break;

    case '-':
        res = lhs - rhs;
        break;

    case '*':
        res = lhs * rhs;
        break;

    case '/':
        assert(rhs != 0 && "div 0(rhs)");
        res = lhs / rhs;
        break;

    default:
        assert(false && "calValueWithOperator unknown operator");
    }

    return res;
}

int calEquation(const string& s)
{
    const char* operators{ "+-*/=" };

    int res{ 0 };
    char selectedOp{ '+' };

    string ReducedEq{ s };

    size_t foundOp{ string::npos };
    foundOp = ReducedEq.find_first_of(operators);

    while (foundOp != string::npos)
    {
        string rhsTxt{ ReducedEq, 0, foundOp};
        res = calValueWithOperator(res, g_numPairs[calHash(rhsTxt)], selectedOp);

        //다음 연산을 위한 갱신
        selectedOp = ReducedEq[foundOp];
        ReducedEq = ReducedEq.substr(foundOp + 1);
        foundOp = ReducedEq.find_first_of(operators);
    }

    return res;
}

int extractAnswer(const string& s)
{
    string ans{ s, s.find_first_of('=') + 1 };
    const auto key = calHash(ans);

    auto iter = g_numPairs.find(key);

    if (iter != end(g_numPairs))
    {
        return iter->second;
    }

    return -1;
}

void score(const string& s)
{
    if (isCorrect(calEquation(s), extractAnswer(s)))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}

int main(void)
{
    preprocess();

    int n{0};
    cin >> n;
    fflushCin();

    vector<string> equations(n);
    for (int i{ 0 }; i < n; ++i)
    {
        string equation{};
        getline(cin, equation);

        equations[i] = std::move(equation);
    }

    for (auto& eq : equations)
    {
        removeWhitespace(eq);
        score(eq);
    }

    return 0;
}