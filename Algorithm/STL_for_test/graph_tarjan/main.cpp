#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>


using namespace std;

using SimpleGraph = vector<vector<int>>;

int findScc(const int node, const SimpleGraph& g, vector<bool>& visited, vector<bool>& finished, stack<int>& historySt, SimpleGraph& sccs)
{
	visited[node] = true;
	historySt.push(node);

    int parent{ node };

    const int currNode{ historySt.top() };
    for (const auto& nextNode : g[currNode])
    {
        if (!visited[nextNode])
            parent = min(parent, findScc(nextNode, g, visited, finished, historySt, sccs));
        else if (!finished[nextNode])
            parent = min(parent, nextNode);
    }

	if (node == parent)
	{
		vector<int> scc;
		while (historySt.top() != parent)
		{
			scc.push_back(historySt.top());
			finished[historySt.top()] = true;
			historySt.pop();
		}

		scc.push_back(historySt.top());
		finished[historySt.top()] = true;
		historySt.pop();
		sccs.push_back(scc);
	}

	return parent;
}

SimpleGraph tarjan(const SimpleGraph& g)
{
	vector<bool> visited(g.size(), false);
	vector<bool> finished(g.size(), false);
	stack<int> historySt;

	SimpleGraph sccs;
	for (auto i{ 0 }; i < g.size(); ++i)
	{
		if (!finished[i])
			findScc(i, g, visited, finished, historySt, sccs);
	}

	return sccs;
}

int main(void)
{
	SimpleGraph g
	{
		{1, 3},
		{2, 4},
		{3, 5},
		{7},
		{2},
		{4, 6},
		{7, 2},
		{8},
		{3}
	};

	//0
	//1
	//2 4 5 6
	//3 8 7
	auto sccs{ tarjan(g) };
	for (const auto& scc : sccs)
	{
		copy(cbegin(scc), cend(scc), ostream_iterator<int>(cout, " "));
		cout << endl;
	}

	return 0;
}