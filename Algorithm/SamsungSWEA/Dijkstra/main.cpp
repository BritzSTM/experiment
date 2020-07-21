/*
    시행착오
    1. 우선순위 큐에 들어간 값(참조)들을 업데이트 해봤자 이미 들어간 값들의 순서가 변경되지 않음
    2. 따라서 두가지 전략중 한가지를 선택해야 함
       1) 변경 가능한 우선순위 큐 구현
       2) 우선순위 큐에서 실패 허용.
          ex) 꺼낸 값이 inf or 꺼낸 값이 최근 cost보다 높으면 실패 값.
    
    선택
    1. 빠른 조회가 가능하므로 간단하게 실패를 허용하기로 함
    2. 우선순위 큐에 들어가는 값은 참조가 아닌 복제 값. 이는 큐의 혼잡성을 높임. 
       하지만 구현은 쉬움.
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <iterator>

using namespace std;

struct SEdge;

struct SNode
{
    int id;
    vector<SEdge> edges;
};

struct SEdge
{
    SNode* pV;
    int weight;
};

using Graph = vector<SNode>;
constexpr int kInf = numeric_limits<int>::max() / 2;

class NodeDistMap
{
public:
    using NodeDist = pair<const SNode*, int>;
    using NodeDistGreater = struct {
        bool operator()(const NodeDist& lhs, const NodeDist& rhs) const noexcept
        {
            return lhs.second > rhs.second;
        }
    };
    using PriorityQueue = priority_queue<NodeDist, vector<NodeDist>, NodeDistGreater>;

public:
    NodeDistMap(const Graph& g)
    {
        for (auto& node : g)
        {
            m_dists.push_back({ &node, kInf });
            m_mapper[&node] = m_dists.size() - 1;
        }
    }

    NodeDist& operator[](const SNode* const pNode)
    {
        return m_dists[m_mapper[pNode]];
    }

    inline NodeDist& operator[](const SNode& node)
    {
        return operator[](addressof(node));
    }

    void printDists()
    {
        for (const auto& n : m_dists)
        {
            cout << "id : " << n.first->id << " dist : " << n.second << endl;
        }
    }

private:
    using SNodePtrHasher = struct {
        size_t operator()(const SNode* const pNode) const noexcept
        {
            return pNode->id;
        }
    };

    vector<NodeDist> m_dists;
    unordered_map<const SNode*, size_t, SNodePtrHasher> m_mapper;
};

void buildGraph(Graph* const pG)
{
    Graph& g = *pG;

    //     s    t    y   x    z
    g = { {0}, {1}, {2}, {3}, {4} };

    g[0].edges = { {&g[1], 10}, {&g[2], 5} };
    g[1].edges = { {&g[2], 2}, {&g[3], 1} };
    g[2].edges = { {&g[1], 3}, {&g[3], 9}, {&g[4], 2} };
    g[3].edges = { {&g[4], 4} };
    g[4].edges = { {&g[0], 7}, {&g[3], 6} };
}

void dijkstra(const Graph& g, const int sID)
{
    // 각 정점의 거리 배열 초기화 [s] = 0, [v] = inf
    NodeDistMap m(g);
    m[g[sID]].second = 0;

    NodeDistMap::PriorityQueue pq;
    pq.push(m[g[sID]]);

    while (!pq.empty())
    {
        // 큐에서 최소 거리 획득
        auto minNode{ pq.top() };
        pq.pop();

        // 실패허용 처리. 나온 값이 현재 구한 가치보다 큰 경우 무시
        if (m[minNode.first].second < minNode.second || minNode.second == kInf)
        {
            continue;
        }
        
        // 인접정점에 대한 릴렉스 실시
        for (const auto& edge : minNode.first->edges)
        {
            auto newDist{ m[minNode.first].second + edge.weight };
            if (newDist < m[edge.pV].second)
            {
                m[edge.pV].second = newDist;
                pq.push(m[edge.pV]);
            }
        }
    }

    m.printDists();
}

int main(void)
{
    Graph g;
    buildGraph(&g);
    dijkstra(g, 0);

    return 0;
}