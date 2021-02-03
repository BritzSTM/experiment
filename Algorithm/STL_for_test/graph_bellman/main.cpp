#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <limits>


using namespace std;

template<typename _T>
struct Edge
{
	unsigned src;
	unsigned dst;
	_T weight;
};

auto bellman(const vector<Edge<int>>& edges, const int vertexCnt, const unsigned start)
{
	vector<int> distances(vertexCnt, numeric_limits<int>::max());
	distances[start] = 0;

	for (auto i{ 0 }; i < vertexCnt - 1; ++i)
	{
		for (const auto& e : edges)
		{
			if (distances[e.src] == numeric_limits<int>::max())
				continue;

			const auto newDist{ distances[e.src] + e.weight };
			if (newDist < distances[e.dst])
				distances[e.dst] = newDist;
		}
	}

	return distances;
}

int main(void)
{
	vector<Edge<int>> edges
	{
		{0, 1, 3},
		{1, 2, 5},
		{1, 3, 10},
		{3, 2, -7},
		{2, 4, 2}
	};

	const auto distances{ bellman(edges, edges.size(), 0) };
	
	int id{ 0 };
	for (const auto& d : distances)
		cout << id++ << " " << d << endl;

	return 0;
}