#include <iostream>
#include <vector>

using namespace std;

class UnionFind final
{
public:
    UnionFind(const int n)
        : m_elems{n, 0}
        , m_ranks(n, 0)
    {
        for (auto i{ 0 }; i < n; ++i)
        {
            m_elems[i] = i;
        }
    }

    int findSet(const int i)
    {
        //return (m_elems[i] == i) ? i : findSet(m_elems[i]);
        return (m_elems[i] == i) ? i : (m_elems[i] = findSet(m_elems[i]));
    }

    bool isSameSet(const int i, const int j)
    {
        return (findSet(i) == findSet(j));
    }

    void unionSet(const int i, const int j)
    {
        if (!isSameSet(i, j))
        {
            auto set1 = findSet(i);
            auto set2 = findSet(j);

            if (m_ranks[set1] > m_ranks[set2])
            {
                m_elems[set2] = set1;
            }
            else
            {
                m_elems[set1] = set2;

                if (m_ranks[set1] == m_ranks[set2])
                {
                    ++m_ranks[set2];
                }
            }
        }
    }

private:
    vector<int> m_elems;
    vector<int> m_ranks;
};

int main(void)
{

    return 0;
}