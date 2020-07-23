#include <iostream>
#include <array>

using namespace std;

array<int, 10> g_datas { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

// 완전이진트리에 필요한 노드의 수를 생각
array<int, 32> g_segmentTree {};

// [ ]
int make_tree(const int lo, const int hi, const int node)
{
    if (lo == hi)
    {
        g_segmentTree[node] = g_datas[lo];
        return g_datas[lo];
    }

    const int mid{ (lo + hi) / 2 };

    g_segmentTree[node] = make_tree(lo, mid, node * 2) + make_tree(mid + 1, hi, node * 2 + 1);

    return g_segmentTree[node];
}

int sum(const int lo, const int hi, const int node, const int qLo, const int qHi)
{
    // 구간 밖
    if (hi < qLo || qHi < lo)
    {
        return 0;
    }

    if (qLo <= lo && hi <= qHi)
    {
        return g_segmentTree[node];
    }

    const int mid{ (lo + hi) / 2 };

    return sum(lo, mid, node * 2, qLo, qHi) + sum(mid + 1, hi, node * 2 + 1, qLo, qHi);
}

void update(const int lo, const int hi, const int node, const int idx, const int diff)
{
    if (idx < lo || hi < idx)
    {
        return;
    }

    g_segmentTree[node] += diff;

    if (lo == hi)
    {
        return;
    }

    const int mid{ (lo + hi) / 2 };

    update(lo, mid, node * 2, idx, diff);
    update(mid + 1, hi, node * 2, idx, diff);
}

int main(void)
{
    make_tree(0, 9, 1);
    cout << sum(0, 9, 1, 0, 9) << endl;
    cout << sum(0, 9, 1, 0, 4) << endl;
    cout << sum(0, 9, 1, 0, 5) << endl;
    cout << sum(0, 9, 1, 7, 9) << endl;

    cout << "update before" << endl;
    cout << sum(0, 9, 1, 0, 4) << endl;

    update(0, 9, 1, 1, 8);

    cout << "update after" << endl;
    cout << sum(0, 9, 1, 0, 4) << endl;

    return 0;
}