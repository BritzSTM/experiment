#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>


using namespace std;

enum class EColor : int
{
	Unknown,
	Red,
	Blue,
	Green,
	Yellow,
	Black,
	White
};

using VertexID = int;

struct SEdge
{
	VertexID srcID;
	VertexID destID;
};

struct SVertex
{
	VertexID id;
	EColor color;
};

SVertex make_vertex(const int id)
{
	return { id, EColor::Unknown };
}

struct VertexHasher
{
	size_t operator()(SVertex const* const pVertex) const noexcept
	{
		return pVertex->id;
	}
};

struct VertexEqualTo
{
	bool operator()(SVertex const* const pLhs, SVertex const* const pRhs) const noexcept
	{
		return pLhs->id == pRhs->id;
	}
};

class CGraph
{
public:
	using edge_list_type = vector<SEdge>;
	using vertex_map_type = unordered_map<SVertex*, edge_list_type, VertexHasher, VertexEqualTo>;

private:
	friend ostream& operator<<(ostream& os, const CGraph& g);

public:
	CGraph(const int vertexCnt)
		: m_vertexCnt{ vertexCnt }
	{
		m_vertexs.reserve(vertexCnt);
	}

	bool SetVertexColor(const VertexID id, const EColor color)
	{
		if (auto it{ find_if(begin(m_vertexs), end(m_vertexs), [&id](const SVertex& v) { return v.id == id; }) }; it != end(m_vertexs))
		{
			it->color = color;
			return true;
		}

		return false;
	}

	bool SetEdges(const int id, edge_list_type list)
	{
		if (m_vertexs.size() < m_vertexCnt)
		{
			m_vertexs.push_back(make_vertex(id));
			m_edge_map.try_emplace(&m_vertexs.back(), move(list));
			return true;
		}

		return false;
	}

private:
	int m_vertexCnt;
	vector<SVertex> m_vertexs;
	vertex_map_type m_edge_map;
};

ostream& operator<<(ostream& os, const CGraph& g)
{
	for (const auto& v : g.m_edge_map){
		os << "[ID] " << v.first->id << " [Color] " << static_cast<int>(v.first->color) << endl;
	}

	return os;
}

void BuildGraph(CGraph& g)
{
    g.SetEdges(1, { {1, 2}, {1, 5} });
    g.SetEdges(2, { {2, 1}, {2, 5}, {2, 4} });
    g.SetEdges(3, { {3, 4}, {3, 7} });
	g.SetEdges(4, { {4, 2}, {4, 3}, {4, 5}, {4, 6}, {4, 8} });
	g.SetEdges(5, { {5, 1}, {5, 2}, {5, 4}, {5, 8} });
	g.SetEdges(6, { {6, 4}, {6, 7}, {6, 8} });
	g.SetEdges(7, { {7, 3}, {7, 6} });
	g.SetEdges(8, { {8, 4}, {8, 5}, {8, 6} });
}

void PaintGraph(CGraph& g)
{
	// 차수가 제일 높은 버택스 부터 알고리즘을 진행해야함.

}

int main(void)
{
	CGraph g(8);
	BuildGraph(g);
	cout << g << endl << endl;

	PaintGraph(g);
	cout << g << endl;
	return 0;
}