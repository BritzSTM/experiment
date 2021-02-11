#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <chrono>


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
		//cout << "부분집합의 원소 갯수 : " << size << endl;

		for (const auto& subset : allSubsets[size])
		{	
			int sum{0};
			
			for_each(cbegin(subset), cend(subset), [&sum](const auto& v) {
				sum += v;
				//cout << v << " ";
				});

			//cout << endl;
			if (sum == target)
				found = true;
		}
	}

	return found;
}

bool GetAllSubsets_memo(const vector<int>& set, int sum, int i, vector<vector<int>>& memo)
{
	if (sum == 0)
		return true;

	if (i == set.size() || set[i] > sum)
		return false;

	// 현재 요소의 합계상태
	if (memo[i][sum] == -1)
	{
		bool append = GetAllSubsets_memo(set, sum - set[i], i + 1, memo);
		bool ignore = GetAllSubsets_memo(set, sum, i + 1, memo);

		memo[i][sum] = append | ignore;
	}

	return memo[i][sum];
}

int main(void)
{
	vector<int> set{ 
		16, 1058, 22, 13, 46, 55, 3, 92, 47, 
		7, 98, 367, 807, 106, 333, 85, 577, 9, 3059 };
	
	const int target{ 6799 };

	using namespace chrono;

	cout << "BF\n";
	auto st{ steady_clock::now() };
	cout << "FT"[static_cast<int>(GetAllSubsets_bf(set, target))] << endl;
	auto et{ steady_clock::now() };
	cout << duration_cast<microseconds>(et - st).count() << endl;
	
	cout << "Memo\n";
	st = steady_clock::now();
	{
		vector<vector<int>> memo(set.size(), vector<int>(7000, -1));
		cout << "FT"[static_cast<int>(GetAllSubsets_memo(set, target, 0, memo))] << endl;
	}
	et = steady_clock::now();
	cout << duration_cast<microseconds>(et - st).count() << endl;

	return 0;
}