#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

class UnionFinder
{
public:
	~UnionFinder() = default;

	UnionFinder(const int nodeCnt)
		: m_nodes(nodeCnt, -1)
		, m_ranks(nodeCnt, 0)
	{
		int id{ 0 };
		for (auto& node : m_nodes){
			node = id++;
		}
	}

	int find(const int node)
	{
		return (node == m_nodes[node]) ? node : (m_nodes[node] = find(m_nodes[node]));
	}

	bool isSameSet(const int s1, const int s2)
	{
		return find(s1) == find(s2);
	}

	void unionSet(const int s1, const int s2)
	{
		const auto s1Root{ find(s1) };
		const auto s2Root{ find(s2) };

		if (s1Root != s2Root)
		{
			// 랭크가 높은 곳에 작은 트리가 붙는다
			if (m_ranks[s1Root] > m_ranks[s2Root])
			{
				m_nodes[s2Root] = s1Root;
			}
			else
			{
				m_nodes[s1Root] = s2Root;

				if (m_ranks[s1Root] == m_ranks[s2Root])
				{
					++m_ranks[s2Root];
				}
			}
		}

		return;
	}

private:
	vector<int> m_ranks;
	vector<int> m_nodes;
};

struct Edge
{
	int v;
	int u;
	int weight;

	bool operator<(const Edge& rhs)
	{
		return weight < rhs.weight;
	}

	friend ostream& operator<<(ostream& os, const Edge& e);
};

ostream& operator<<(ostream& os, const Edge& e)
{
	os << "[u] " << e.u << " [v] " << e.v << " [w] " << e.weight;
	return os;
}

vector<Edge> BuildGraph()
{
	vector<Edge> g;
	g.reserve(12);

	g.push_back({ 1, 2, 2 });
	g.push_back({ 1, 5, 3 });

	g.push_back({ 2, 1, 2 });
	g.push_back({ 2, 5, 5 });

	g.push_back({ 2, 4, 1 });
	g.push_back({ 3, 4, 2 });
	g.push_back({ 3, 7, 3 });

	g.push_back({ 4, 2, 1 });
	g.push_back({ 4, 3, 2 });
	g.push_back({ 4, 5, 2 });
	g.push_back({ 4, 6, 4 });
	g.push_back({ 4, 8, 5 });

	g.push_back({ 5, 1, 3 });
	g.push_back({ 5, 2, 5 });
	g.push_back({ 5, 4, 2 });
	g.push_back({ 5, 8, 3 });

	g.push_back({ 6, 4, 4 });
	g.push_back({ 6, 7, 4 });
	g.push_back({ 6, 8, 1 });

	g.push_back({ 7, 3, 3 });
	g.push_back({ 7, 6, 4 });

	g.push_back({ 8, 4, 5 });
	g.push_back({ 8, 5, 3 });
	g.push_back({ 8, 6, 1 });

	return g;
}

vector<Edge> BuildKruskalMst(vector<Edge>& g, const int nodeCnt)
{
	vector<Edge> mst;
	mst.reserve(g.size());
	
	sort(begin(g), end(g));
	UnionFinder uf(nodeCnt + 1);

	for (const auto& e : g)
	{
		if (!uf.isSameSet(e.u, e.v))
		{
			uf.unionSet(e.u, e.v);
			mst.push_back(e);
		}
	}

	return mst;
}

int main(void)
{
	auto g{ BuildGraph() };
	auto mst{ BuildKruskalMst(g, 8) };

	copy(cbegin(mst), cend(mst), ostream_iterator<Edge>(cout, "\n"));

	return 0;
}