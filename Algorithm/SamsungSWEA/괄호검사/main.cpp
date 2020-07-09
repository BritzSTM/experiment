#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>
#include <cassert>

using namespace std;



inline void setupBrackets(char (&brackets)[255]) noexcept
{
    brackets['('] = ')';
    brackets[')'] = '(';

    brackets['['] = ']';
    brackets[']'] = '[';

    brackets['{'] = '}';
    brackets['}'] = '{';

    brackets['<'] = '>';
    brackets['>'] = '<';
}

inline bool isOpenBracket(const char c) noexcept
{
    return ( c == '(' || c == '[' || c == '{' || c == '<' );
}

inline bool isCloseBracket(const char c) noexcept
{
    return (c == ')' || c == ']' || c == '}' || c == '>');
}

// 비 유효하다면 비유효한 지점을 second에 저장
pair<bool, int> isValidBk(const string& s)
{
    char brackets[255]{};
    setupBrackets(brackets);

    bool validBk{ true };
    stack<char> st;
    int i{ 0 };

    for (i = 0 ; i < s.size(); ++i)
    {
        if (isOpenBracket(s[i]))
        {
            st.push(s[i]);
        }
        else if (isCloseBracket(s[i]))
        {
            if (!st.empty() && (st.top() == brackets[s[i]]))
            {
                st.pop();
            }
            else
            {
                validBk = false;
                break;
            }
        }
        else
        {
            continue;
        }
    }
    
    if (!st.empty())
    {
        validBk = false;
    }

    return {validBk, i};
}

int main(void)
{
    // 17 length 
    string input1{ "{[()]}<>[<{}><>[" };
    string input2{ "{[()]}<>[<{}><>]" };
    string input3{ "{[()]}<>[<{)><>]" };

    auto res1 = isValidBk(input1);
    assert(res1.first == false && res1.second == 16 );

    auto res2 = isValidBk(input2);
    assert(res2.first == true);

    auto res3 = isValidBk(input3);
    assert(res3.first == false && res3.second == 11);

    return 0;
}