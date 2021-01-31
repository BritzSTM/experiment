#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <set>


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
	edge_map[1] = { {2, 0} };
	edge_map[2] = { {1, 0}, {3, 0}, {8, 0} };
	edge_map[3] = { {2, 0}, {4, 0} };
	edge_map[4] = { {3, 0}, {6, 0} };
	edge_map[5] = { {7, 0}, {9, 0} };
	edge_map[6] = { {4, 0} };
	edge_map[7] = { {5, 0} };
	edge_map[8] = { {2, 0}, {9, 0} };
	edge_map[9] = { {5, 0}, {8, 0} };

	for (auto& src : edge_map)
		for (auto& dst : src.second)
			g.add_edge( Edge<_T>{src.first, dst.first, dst.second });

	return g;
}

template<typename _T>
pair<vector<pair<unsigned, bool>>, bool> IsBipartiteGraph(const Graph<_T>& g)
{
	bool paint{ false };
	map<unsigned, bool> colorMap;
	set<unsigned> vSet;

	stack<unsigned> st;
	deque<unsigned> vHistory;
	vector<pair<unsigned, bool>> res;

	st.push(1);	
	vHistory.push_back(0);
	vHistory.push_back(0);
	
	bool isBG{ true };
	while (!st.empty())
	{
		// 미방문 정점
		if (vSet.find(st.top()) == cend(vSet))
		{
			// 현재정점 설정
			vHistory.pop_front();
			vHistory.push_back(st.top());
			
			// 방문표시
			vSet.insert(st.top());
			st.pop();

			// paint
			if (vHistory.front() == 0)
				colorMap[vHistory.back()] = paint;
			else
			{
				if (colorMap[vHistory.front()] == paint)
				{
					isBG = false;
					break;
				}
				else
					colorMap[vHistory.back()] = paint;
			}
			res.emplace_back(vHistory.back(), paint);
			paint = !paint;

			// 미방문 정점 삽입
			const auto edges{ g.edges(vHistory.back()) };
			for_each(cbegin(edges), cend(edges), [&vSet, &st](const auto& e) { 
				if (vSet.find(e.dst) == cend(vSet))
					st.push(e.dst);
				});
		}
	}
	
	return make_pair(move(res), isBG);
}

int main(void)
{
	auto g{ create_reference_graph<unsigned>() };
	cout << g << endl;

	auto res{ IsBipartiteGraph(g) };
	if (res.second)
	{
		cout << "is bg" << endl;
		for (const auto& v : res.first)
		{
			cout << v.first << " : ";
			(v.second == false) ? cout << "Black" : cout << "Red";
			cout << endl;
		}
	}
	else
		cout << "is not bg" << endl;

	return 0;
}