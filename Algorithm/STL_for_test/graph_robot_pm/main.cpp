#include <iostream>
#include <string>
#include <sstream>
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
struct Label
{
	unsigned ID;
	_T distance;

	bool operator>(const Label<_T>& rhs)
	{
		return this->distance > rhs.distance;
	}
};

using SignEdge = Edge<int>;
using SignLabel = Label<int>;
using TestCase = pair<string, int>;

vector<SignEdge> buildMap(const TestCase& tc)
{
	unsigned srcID{ 0 };
	stringstream ss{ tc.first };

	int mapSize;
	ss >> mapSize;

	vector<SignEdge> resMap;
	string edgesPm, weightPm;
	while ((ss >> edgesPm >> weightPm) && !ss.eof())
	{
		const int weight{ stoi(weightPm) * -1 };

		for (const auto& c : edgesPm)
		{
			if (c == 'W')
				resMap.emplace_back(SignEdge{ srcID, srcID - 1, weight });
			else if (c == 'E')
				resMap.emplace_back(SignEdge{ srcID, srcID + 1, weight });
			else if (c == 'N')
				resMap.emplace_back(SignEdge{ srcID, srcID - mapSize, weight });
			else // S
				resMap.emplace_back(SignEdge{ srcID, srcID + mapSize, weight });
		}

		++srcID;
	}

	return resMap;
}

int searchPath(const vector<SignEdge>& edges, const unsigned mapSize)
{
	const auto vertexCnt{ mapSize * mapSize };
	vector<int> distances(vertexCnt, numeric_limits<int>::max());
	distances[0] = 0;

	auto RelexEdges{
		[&distances, &edges]() -> bool{
			bool update{false};

			for (const auto& e : edges)
			{
				if (distances[e.src] == numeric_limits<int>::max())
					continue;

				const auto newDist{ distances[e.src] + e.weight };
				if (newDist < distances[e.dst])
				{
					update = true;
					distances[e.dst] = newDist;
				}
			}

			return update;
	}};

	// 알고리즘 진행
	for (auto i{ 0 }; i < vertexCnt - 1; ++i)
		RelexEdges();

	// 음수 사이클 검사
	if (RelexEdges())
		return -1;

	return distances.back() * -1;
}

int main(void)
{
	TestCase tcs[]
	{
		{"3\nSE -10\nSE -8\nS -6\nS 7\nE -10\nS 20\nE -1\nNE 5\n", 11},
		{"3\nE -1\nE -5\nS 6\nS -2\nW 15\nW -10\nE -5\nNE 5\n", -1},
		{"4\nS -83\nE -77\nSE -93\nS 86\nSE -49\nN -62\nSE -90\nS -63\nS 40\nNW -72\nSW -11\nW 67\nE -82\nN -62\nE -67\n", -352}
	};

	for (const auto& tc : tcs)
	{
		const auto& map{ buildMap(tc) };

		const auto res{ searchPath(map, stoi(tc.first))};
		if (res == tc.second)
			cout << "correct : " << res << "\n\n";
		else
			cout << "fail test case\n" << "expects : " << tc.second << " ans : " << res << endl << "case param\n" << tc.first <<endl;
	}

	return 0;
}