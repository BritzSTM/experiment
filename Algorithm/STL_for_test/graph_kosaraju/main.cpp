#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <map>


using namespace std;

using AdjList = vector<vector<int>>;

void FillStack(const int node, vector<bool>& visited, stack<int>& st, const AdjList& adj)
{
	visited[node] = true;

	for (const auto& nextNode : adj[node])
	{
		if (!visited[nextNode])
			FillStack(nextNode, visited, st, adj);
	}

	st.push(node);
}

AdjList Transpose(const int nodeCnt, const AdjList& adj)
{
	AdjList tAdj(nodeCnt);

	for (auto i{ 0 }; i < nodeCnt; ++i)
	{
		for (const auto& node : adj[i])
		{
			tAdj[node].push_back(i);
		}
	}

	return tAdj;
}

void CollectConnectedComponents(const int node, vector<bool>& visited, const AdjList& adj, vector<int>& component)
{
	visited[node] = true;
	component.push_back(node);

	for (const auto& nextNode : adj[node])
	{
		if (!visited[nextNode])
			CollectConnectedComponents(nextNode, visited, adj, component);
	}
}

AdjList kosaraju(const int nodeCnt, const AdjList adj)
{
	vector<bool> visited(nodeCnt, false);
	stack<int> st;

	for (auto i{ 0 }; i < nodeCnt; ++i)
	{
		if (!visited[i])
			FillStack(i, visited, st, adj);
	}

	AdjList tAdj{ Transpose(nodeCnt, adj) };
	fill(begin(visited), end(visited), false);
	
	AdjList ccs;
	while (!st.empty())
	{
		const auto node{ st.top() };
		st.pop();

		if (!visited[node])
		{
			vector<int> c;
			CollectConnectedComponents(node, visited, tAdj, c);
			ccs.push_back(c);
		}
	}

	return ccs;
}

int main(void)
{
	AdjList adj{
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

	auto ccs{ kosaraju(adj.size(), adj) };
	for (const auto& g : ccs)
	{
		copy(cbegin(g), cend(g), ostream_iterator<int>(cout, " "));
		cout << endl;
	}

	return 0;
}