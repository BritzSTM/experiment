#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct SGraphNode;
using GraphSet = vector<SGraphNode>;

struct SEdge
{
    SGraphNode* node;
    int weight;
};

using AdjGraphSet = vector<SEdge>;

struct SGraphNode
{
    int id;
    AdjGraphSet adjNodes;
};

using Visiting = vector<bool>;

void buildGraph(GraphSet& nodeSet)
{
    /*
        Node : 8
        1 : 2 3 5
        2 : 1 4 5 6
        3 : 1 5
        4 : 2 6
        5 : 1 2 3 7
        6 : 2 4 7
        7 : 5 6 8
        8 : 7
    */
    nodeSet = { {-1}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8} };
    
    nodeSet[1].adjNodes.push_back({ &nodeSet[2], 1 });
    nodeSet[1].adjNodes.push_back({ &nodeSet[3], 1 });
    nodeSet[1].adjNodes.push_back({ &nodeSet[5], 1 });

    nodeSet[2].adjNodes.push_back({ &nodeSet[1], 1 });
    nodeSet[2].adjNodes.push_back({ &nodeSet[4], 1 });
    nodeSet[2].adjNodes.push_back({ &nodeSet[5], 1 });
    nodeSet[2].adjNodes.push_back({ &nodeSet[6], 1 });

    nodeSet[3].adjNodes.push_back({ &nodeSet[1], 1 });
    nodeSet[3].adjNodes.push_back({ &nodeSet[5], 1 });

    nodeSet[4].adjNodes.push_back({ &nodeSet[2], 1 });
    nodeSet[4].adjNodes.push_back({ &nodeSet[6], 1 });

    nodeSet[5].adjNodes.push_back({ &nodeSet[1], 1 });
    nodeSet[5].adjNodes.push_back({ &nodeSet[2], 1 });
    nodeSet[5].adjNodes.push_back({ &nodeSet[3], 1 });
    nodeSet[5].adjNodes.push_back({ &nodeSet[7], 1 });

    nodeSet[6].adjNodes.push_back({ &nodeSet[2], 1 });
    nodeSet[6].adjNodes.push_back({ &nodeSet[4], 1 });
    nodeSet[6].adjNodes.push_back({ &nodeSet[7], 1 });

    nodeSet[7].adjNodes.push_back({ &nodeSet[5], 1 });
    nodeSet[7].adjNodes.push_back({ &nodeSet[6], 1 });
    nodeSet[7].adjNodes.push_back({ &nodeSet[8], 1 });

    nodeSet[7].adjNodes.push_back({ &nodeSet[7], 1 });
}

namespace _internal
{
    void bfs(const GraphSet& nodeSet, Visiting& checker, queue<const SGraphNode*>& sq)
    {
        if (!sq.empty())
        {
            auto node{ sq.front() };
            cout << node->id << endl;
            sq.pop();

            for (auto& adjNode : node->adjNodes)
            {
                const auto& adjID{ adjNode.node->id };

                if (!checker[adjID])
                {
                    checker[adjID] = true;
                    sq.push(&nodeSet[adjID]);
                }
            }

            bfs(nodeSet, checker, sq);
        }
    }

    void dfs(const GraphSet& nodeSet, Visiting& checker, const int v)
    {
        checker[v] = true;

        cout << v << endl;

        for (auto& adjNode : nodeSet[v].adjNodes)
        {
            const auto& adjID = adjNode.node->id;

            if (!checker[adjID])
            {
                dfs(nodeSet, checker, adjID);
            }
        }
    }
}

void bfs(const GraphSet& nodeSet, const int v)
{
    Visiting checker(nodeSet.size(), false);
    queue<const SGraphNode*> sq;

    checker[v] = true;
    sq.push(&nodeSet[v]);

    _internal::bfs(nodeSet, checker, sq);
}

void bfsIter(const GraphSet& nodeSet, const int v)
{
    Visiting checker(nodeSet.size(), false);
    queue<const SGraphNode*> sq;
    sq.push(&nodeSet[v]);
    checker[v] = true;

    while (!sq.empty())
    {
        const auto node{ sq.front()};
        cout << node->id << endl;
        sq.pop();
        
        for (const auto& adjNode : node->adjNodes)
        {
            const auto adjID{ adjNode.node->id };

            if (!checker[adjID])
            {
                checker[adjID] = true;
                sq.push(&nodeSet[adjID]);
            }
        }
    }
}

void dfs(const GraphSet& nodeSet, const int v)
{
    Visiting checker(nodeSet.size(), false);
    _internal::dfs(nodeSet, checker, v);
}

int main(void)
{
    GraphSet nodeSet;
    buildGraph(nodeSet);

    cout << "dfs" << endl;
    dfs(nodeSet, 1);

    cout << "bfs" << endl;
    bfs(nodeSet, 1);

    cout << "bfsIter" << endl;
    bfsIter(nodeSet, 1);

    return 0;
}