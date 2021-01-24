#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <set>


using namespace std;

enum EColor : int
{
	Unknown,
	_First = 1,
	Red = 1,
	Blue,
	Green,
	Yellow,
	Black,
	White,
	_Last
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
	using vertex_map_type = unordered_map<const SVertex*, edge_list_type, VertexHasher, VertexEqualTo>;

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

	edge_list_type GetEdges(const VertexID id) const
	{
		auto it{ find_if(cbegin(m_vertexs), cend(m_vertexs), [&id](const auto& v) { return v.id == id; }) };
		return m_edge_map.at(&(*it));
	}

	vector<pair<SVertex, size_t>> GetVertexs() const
	{
		vector<pair<SVertex, size_t>> res;
		res.reserve(m_vertexCnt);

		for (const auto& v : m_vertexs)
		{
			const auto degree{ m_edge_map.at(addressof(v)).size() };
			res.push_back(make_pair(v, degree));
		}

		return res;
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
	auto vertexs{ g.GetVertexs() };
	sort(begin(vertexs), end(vertexs), [](const auto& v1, const auto& v2) { return v1.second > v2.second; });

	const auto un_finder{ [&vertexs]() {return find_if(begin(vertexs), end(vertexs), [](const auto& v) { return v.first.color == EColor::Unknown; }); } };
	const auto get_dest{ [&vertexs](const VertexID id) { return find_if(begin(vertexs), end(vertexs), [&id](const auto& v) { return v.first.id == id; }); } };

	auto it{ vertexs.end() };
	while ((it = un_finder()) != end(vertexs))
	{
		// 인근에 할당되지 않은 색상 찾기
		set<EColor> assignedColors{};
		for (const auto& e : g.GetEdges(it->first.id))
		{
			auto destIt{ get_dest(e.destID) };

			if (destIt != vertexs.end())
			{
				if (destIt->first.color != EColor::Unknown)
					assignedColors.insert(destIt->first.color);
			}
		}

		EColor foundColor{ EColor::Unknown };
		for (int c{ EColor::_First }; c < EColor::_Last; ++c)
		{
			if (assignedColors.find(static_cast<EColor>(c)) == assignedColors.end())
			{
				foundColor = static_cast<EColor>(c);
				break;
			}
		}

		// 자신의 정점과 다른 정점들의 인근에 해당색상이 없을때 칠한다
		it->first.color = foundColor;
		for (auto& v : vertexs)
		{
			if (v.first.color == EColor::Unknown)
			{
				bool notFound{ true };
				for (const auto& e : g.GetEdges(v.first.id))
				{
					auto destIt{ get_dest(e.destID) };
					if (destIt != vertexs.end())
					{
						if (destIt->first.color == foundColor)
						{
							notFound = false;
							break;
						}
					}
				}

				if (notFound)
				{
					v.first.color = foundColor;
				}
			}
		}
	}

	for (const auto& v : vertexs)
	{
		g.SetVertexColor(v.first.id, v.first.color);
	}
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