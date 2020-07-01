/*
    https://www.algospot.com/judge/submission/recent/
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

string reversQuadTree(string::iterator& iter)
{
    char node = *iter;
    ++iter;

    if (node == 'w' || node == 'b')
    {
        return string(1, node);
    }

    string _1 = reversQuadTree(iter);
    string _2 = reversQuadTree(iter);
    string _3 = reversQuadTree(iter);
    string _4 = reversQuadTree(iter);

    stringstream s;
    s << "x" << _3 << _4 << _1 << _2;

    return s.str();
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int testCase{};
    cin >> testCase;

    vector<string> res;
    res.reserve(testCase);

    while (testCase--)
    {
        string s;
        cin >> s;

        auto iter = s.begin();
        res.push_back(reversQuadTree(iter));
    }
    
    copy(begin(res), end(res), ostream_iterator<string>{cout, "\n"});

    return 0;
}