#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

int main(void)
{
    vector<int> vec{ 1, 2, 3, 8, 0, 9, 9, 0, 8, 4 };
    vector<int> expects{ 1, 2, 3, 4 };

    stack<int> st;
    for (auto& n : vec)
    {
        if (!st.empty())
        {
            if (st.top() == n)
            {
                st.pop();
            }
            else
            {
                st.push(n);
            }
        }
        else
        {
            st.push(n);
        }
    }

    vec.resize(4);
    for (int i( st.size() - 1 ); i >= 0; --i)
    {
        vec[i] = st.top();
        st.pop();
    }

    assert(vec == expects);

    return 0;
}