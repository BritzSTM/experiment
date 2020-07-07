/*
    https://programmers.co.kr/learn/courses/30/lessons/42584
*/
#include <vector>
#include <stack>
#include <utility>

using namespace std;

using SPC = std::pair<int, int>;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());

    stack<SPC> stack;
    stack.push(make_pair(prices.back(), 0));

    for (int i = prices.size() - 2; i >= 0; --i)
    {
        int accDay{ 1 };

        while (!stack.empty() && prices[i] <= stack.top().first)
        {
            auto last = stack.top();
            accDay += last.second;
            stack.pop();
        }

        stack.push(make_pair(prices[i], accDay));
        answer[i] = accDay;
    }

    return answer;
}