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
	edge_map[1] = { {2, 2}, {5, 3} };
	edge_map[2] = { {1, 2}, {5, 5}, {4, 1} };
	edge_map[3] = { {4, 2}, {7, 3} };
	edge_map[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
	edge_map[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3}};
	edge_map[6] = { {4, 4}, {7, 4}, {8, 1} };
	edge_map[7] = { {3, 3}, {6, 4} };
	edge_map[8] = { {4, 5}, {5, 3}, {6, 1} };

	for (auto& src : edge_map)
		for (auto& dst : src.second)
			g.add_edge( Edge<_T>{src.first, dst.first, dst.second });

	return g;
}

template<typename _T>
struct Label
{
	unsigned ID;
	_T distance;

	bool operator>(const Label<_T>& rhs) const noexcept
	{
		return this->distance > rhs.distance;
	}
};

template<typename _T>
auto prim_mst(const Graph<_T>& g, const unsigned ID)
{
	vector<bool> visited(g.vertices(), false);
	vector<unsigned> distances(g.vertices(), numeric_limits<unsigned>::max());
	priority_queue<Label<_T>, vector<Label<_T>>, greater<Label<_T>>> queue;

	vector<unsigned> res;
	distances[ID] = 0;
	queue.push({ ID, 0 });

	while (!queue.empty())
	{
		const auto currVtx{ queue.top() };
		queue.pop();

		if (!visited[currVtx.ID])
		{
			visited[currVtx.ID] = true;
			res.push_back(currVtx.ID);

			for (const auto& e : g.edges(currVtx.ID))
			{
				const auto newDist{ e.weight };

				if (newDist < distances[e.dst])
				{
					distances[e.dst] = newDist;
					queue.push({ e.dst, newDist });
				}
			}
		}
	}

	return res;
}

int main(void)
{
	auto g{ create_reference_graph<unsigned>() };
	cout << g << endl;
	
	cout << "prim mst" << endl;
	for (const auto& v : prim_mst(g, 1))
		cout << v << endl;

	return 0;
}