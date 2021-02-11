#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


using namespace std;

void GetAllSubsets_bf(
	const vector<int>& set, vector<int> subset, int index, vector<vector<vector<int>>>& allSubsets)
{
	if (index == set.size())
	{
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	GetAllSubsets_bf(set, subset, index + 1, allSubsets);

	subset.push_back(set[index]);
	GetAllSubsets_bf(set, subset, index + 1, allSubsets);
}

bool GetAllSubsets_bf(const vector<int>& set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets_bf(set, {}, 0, allSubsets);

	bool found{ false };
	for (auto size{ 0 }; size < allSubsets.size(); ++size)
	{
		cout << "부분집합의 원소 갯수 : " << size << endl;

		for (const auto& subset : allSubsets[size])
		{	
			int sum{0};
			
			for_each(cbegin(subset), cend(subset), [&sum](const auto& v) {
				sum += v;
				cout << v << " ";
				});

			cout << endl;
			if (sum == target)
				found = true;
		}
	}

	return found;
}

int main(void)
{
	vector<int> set{ 13, 79, 45, 29 };
	
	cout << "FT"[static_cast<int>(GetAllSubsets_bf(set, 58))];

	return 0;
}