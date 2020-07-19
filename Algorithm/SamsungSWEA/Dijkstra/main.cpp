#include <iostream>
#include <vector>

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

Graph dj(const Graph& g, const int s, const int d);

int main(void)
{
    Graph g;
    buildGraph(&g);

    return 0;
}