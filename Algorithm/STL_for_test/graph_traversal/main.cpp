#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>


using namespace std;

template<typename _T>
struct Edge
{
	unsigned src;
	unsigned dst;
	_T weight;
};

template<typename _T>
class Graph
{
public:
	Graph(unsigned N) : V{ N } {}

	auto vertices() const { return V; }

	auto& edges() const { return edge_list };

	auto edges(unsigned v) const
	{
		vector<Edge<_T>> edges_from_v;
		for (auto& e : edge_list)
		{
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}
		
		return edges_from_v;
	}

	void add_edge(Edge<_T>&& e)
	{
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
			edge_list.emplace_back(e);
		else
			cerr << "Error vertex id" << endl;
	}

	template<typename _U>
	friend ostream& operator<<(ostream& os, const Graph<_U>& g);

private:
	unsigned V;
	vector<Edge<_T>> edge_list;
};

template<typename _U>
ostream& operator<<(ostream& os, const Graph<_U>& g)
{
	for (unsigned i{ 1 }; i < g.vertices(); ++i)
	{
		os << i << ":\t";

		for (auto& e : g.edges(i))
			os << "{" << e.dst << ": " << e.weight << "}, ";

		os << endl;
	}

	return os;
}

template<typename _T>
auto create_reference_graph()
{
	Graph<_T> g(9);

	map<unsigned, vector<pair<unsigned, _T>>> edge_map;
	edge_map[1] = { {2, 0}, { 5, 0 } };
	edge_map[2] = { {1, 0}, {5, 0}, {4, 0} };
	edge_map[3] = { {4, 0}, {7, 0} };
	edge_map[4] = { {2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0} };
	edge_map[5] = { {1, 0}, {2, 0}, {4, 0}, {8, 0}};
	edge_map[6] = { {4, 0}, {7, 0}, {8, 0} };
	edge_map[7] = { {3, 0}, {6, 0} };
	edge_map[8] = { {4, 0}, {5, 0}, {6, 0} };

	for (auto& src : edge_map)
		for (auto& dst : src.second)
			g.add_edge( Edge<_T>{src.first, dst.first, dst.second });

	return g;
}

template<typename _T>
vector<unsigned> bfs(const Graph<_T>& g)
{
	vector<unsigned> vHistory;
	vector<bool> vFlag(g.vertices() + 1ull, false);

	queue<unsigned> queue;
	queue.push(1);

	while (!queue.empty())
	{
		const auto v{ queue.front() };
		queue.pop();

		if (!vFlag[v])
		{
			vHistory.push_back(v);
			vFlag[v] = true;			

			const auto edges{ g.edges(v) };
			for (const auto& e : edges) {
				queue.push(e.dst);
			}
		}
	}

	return vHistory;
}

template<typename _T>
vector<unsigned> dfs(const Graph<_T>& g)
{
	vector<unsigned> vHistory;
	vector<bool> vFlag(g.vertices() + 1ull, false);

	stack<unsigned> st;
	st.push(1);

	while (!st.empty())
	{
		const auto v{ st.top() };
		st.pop();

		if (!vFlag[v])
		{
			vHistory.push_back(v);
			vFlag[v] = true;

			const auto edges{ g.edges(v) };
			for (const auto& e : edges)
			{
				st.push(e.dst);
			}
		}
	}

	return vHistory;
}

int main(void)
{
	auto g{ create_reference_graph<unsigned>() };
	cout << g << endl;

	auto bfsRes{ bfs(g) };
	cout << "bfs result : ";
	copy(cbegin(bfsRes), cend(bfsRes), ostream_iterator<unsigned>(cout, " "));
	cout << endl;

	auto dfsRes{ dfs(g) };
	cout << "dfs result : ";
	copy(cbegin(dfsRes), cend(dfsRes), ostream_iterator<unsigned>(cout, " "));
	cout << endl;

	return 0;
}