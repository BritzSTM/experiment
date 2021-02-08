#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;

struct Edge
{
	unsigned dst;
	int flow;
	int capacity;
};

using SimpleGraph = vector<vector<Edge>>;

SimpleGraph BuildNegativeEdges(const SimpleGraph& g)
{
	SimpleGraph target(g);

	for (auto i{ 0 }; i < g.size(); ++i)
	{
		for (const auto& edge : g[i])
		{
			target[edge.dst].push_back({static_cast<unsigned>(i), 0, 0}); // 용량이 0인 것이 특징
		}
	}

	return target;
}

int edmonds_maxFlow(const SimpleGraph& g, const int start, const int end)
{
	auto sg{ BuildNegativeEdges(g) };
	
	int res{};
	// 경로가 없을때 까지 반복
	while (1)
	{
		vector<int> parent(sg.size());
		vector<bool> visited(sg.size(), false);
		queue<int> q;

		q.push(start);
		visited[start] = true;
		while (!q.empty())
        {
            const int currNode{ q.front() };
            q.pop();

            for (const auto& e : sg[currNode])
            {
                if ((e.capacity - e.flow) > 0 && !visited[e.dst])
                {
                    visited[e.dst] = true;
					parent[e.dst] = currNode;
                    q.push(e.dst);

					if (e.dst == end) break;
                }
            }
        }

		if (!visited[end]) break;

		auto findDstEdge{ [&sg](const int src, const int dst) {
			return find_if(sg[src].begin(), sg[src].end(), [&dst](const auto& edge) { return edge.dst == dst; });
		} };

		int minFlow{ numeric_limits<int>::max() };
		for (auto node{ end }; node != start; node = parent[node])
		{
			auto edgeIt{ findDstEdge(parent[node], node) };
			minFlow = min(minFlow, edgeIt->capacity - edgeIt->flow);
		}

        // 유량 추가
        for (auto node{ end }; node != start; node = parent[node])
        {
            auto sEdgeIt{ findDstEdge(parent[node], node) };
            sEdgeIt->flow += minFlow;

            auto uEdgeIt{ findDstEdge(node, parent[node]) };
            uEdgeIt->flow -= minFlow;
        }

		res += minFlow;
	}

	return res;
}

int main(void)
{
	SimpleGraph g
	{
		{}, // dummy
		{{2, 0, 12}, {4, 0, 11}},
		{{3, 0, 6}, {4, 0, 3}, {5, 0, 5}, {6, 0, 9}},
		{{6, 0, 8}},
		{{5, 0, 9}},
		{{3, 0, 3}, {6, 0, 4}},
		{}
	};

	// 19
	cout << edmonds_maxFlow(g, 1, 6) << endl;

	return 0;
}