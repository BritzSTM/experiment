/*
    수식타입을 팬텀타입으로 구현

    CMAKE_CXX_STANDARD 17 필수
*/
#include <iostream>
#include <string>
#include <sstream>
#include <optional>
#include <stack>

using namespace std;

struct Prefix {};
struct Infix {};

template<typename _Fix>
struct SExpression
{
    string data;
    bool valid;
};

namespace _internal
{
    // + - * / ( ) 만 지원함
    optional<int> getOperatorRank(const char c) noexcept
    {
        switch (c)
        {
        case '(':
        case ')':
            return { 0 };
            break;
        
        case '+':
        case '-':
            return { 1 };
            break;

        case '*':
        case '/':
            return { 2 };
            break;

        default:
            return {};
        }

        return {};
    }
}

// 후위 수식으로 변환
SExpression<Prefix> toPrefixExp(const SExpression<Infix> exp)
{
    using _internal::getOperatorRank;

    stringstream builder;
    bool validExp{ true };
    stack<char> st;

    for (const auto& elem : exp.data)
    {
        auto rank = getOperatorRank(elem);

        if (rank)
        {
            if (st.empty())
            {
                st.push(elem);
            }
            else
            {
                if (elem == '(')
                {
                    st.push(elem);
                }
                else if (elem == ')')
                {
                    while (!st.empty() && (st.top() != '('))
                    {
                        builder << st.top();
                        st.pop();
                    }

                    if (st.empty())
                    {
                        validExp = false;
                        break;
                    }
                    else
                    {
                        st.pop();
                    }
                }
                else
                {
                    // 스택 상위에 있는 연산자가 순위가 낮아야 함
                    while (!st.empty() && (getOperatorRank(st.top()) >= rank))
                    {
                        builder << st.top();
                        st.pop();
                    }

                    st.push(elem);
                }
            }
        }
        else
        {
            builder << elem;
        }
    }

    while (!st.empty())
    {
        builder << st.top();
        st.pop();
    }

    return { builder.str(), validExp };
}

// 후위 수식을 계산한 후 반환
template<typename _Res>
_Res CalPrefixExp(const SExpression<Prefix> exp);

int main(void)
{
    SExpression<Infix> exp1{ "(1+2)+3*2" };
    SExpression<Infix> exp2{ "(2+5)*3*(2+1)" }; //25+3*21+*

    auto prefixExp{ toPrefixExp(exp2) };

    //cout << CalPrefixExp<int>(prefixExp);

    return 0;
}