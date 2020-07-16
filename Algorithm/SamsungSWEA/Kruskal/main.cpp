#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

struct SEdge
{
    int v;
    int u;
    int weight;
};

using EdgeGraph = vector<SEdge>;

class UnionFinder final
{
public:
    UnionFinder(const int n)
        : m_elems(n, -1)
        , m_rank(n, 0)
    {
        iota(begin(m_elems), end(m_elems), 0);
    }

    int findSet(const int x)
    {
        return (m_elems[x] == x) ? x : (m_elems[x] = findSet(m_elems[x]));
    }

    bool isSameSet(const int x, const int y)
    {
        return findSet(x) == findSet(y);
    }

    void unionSet(const int x, const int y)
    {
        if (!isSameSet(x, y))
        {
            auto set1{ findSet(x) };
            auto set2{ findSet(y) };

            if (m_rank[set1] > m_rank[set2])
            {
                m_elems[set2] = set1;
            }
            else
            {
                m_elems[set1] = set2;

                if (m_rank[set1] == m_rank[set2])
                {
                    ++m_rank[set2];
                }
            }
        }
    }

private:
    vector<int> m_elems;
    vector<int> m_rank;
};

void kruskal(const EdgeGraph& g, const int nodeCnt)
{
    // 간선을 뒤에서 부터 소모하기 위해 내림차순 정렬
    EdgeGraph edges{ g };
    sort(begin(edges), end(edges), [](auto& edge1, auto& edge2)
        {
            return edge1.weight > edge2.weight;
        });


    // n - 1개의 간선이 획득되어야 함
    const int pickCnt{ nodeCnt - 1 };

    // 트리집합 구분
    UnionFinder treeSet{ nodeCnt };

    // 선택된 간선 집합
    EdgeGraph spt;
    spt.reserve(pickCnt);

    while (spt.size() < pickCnt)
    {
        const auto minEdge{ edges.back() };
        edges.pop_back();

        // 두 간선이 같은 집합이 아니라면 선택하고 집합 병합
        if (!treeSet.isSameSet(minEdge.u, minEdge.v))
        {
            treeSet.unionSet(minEdge.u, minEdge.v);
            spt.push_back(minEdge);
        }
    }

    for (const auto& e : spt)
    {
        cout << e.v << " " << e.u << " " << e.weight << endl;
    }
}

EdgeGraph buildGraph()
{
    // 7개의 노드로 구성된 그래프
    return
    {
        {0, 1, 32},
        {0, 2, 31},
        {0, 5, 60},
        {0, 6, 51},
        {1, 2, 21},
        {2, 4, 46},
        {2, 6, 25},
        {3, 4, 34},
        {3, 5, 18},
        {4, 5, 40},
        {4, 6, 51},
    };
}

int main(void)
{
    EdgeGraph graph{ buildGraph() };
    kruskal(graph, 7);

    return 0;
}