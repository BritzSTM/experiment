#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> g_foundBfLCS;

int findLCS_bf(const string& a, const string& b, const int i, const int j, vector<pair<int, int>> subseq)
{
	// 문자열 길이를 초과한 경우
	if (a.size() <= i || b.size() <= j)
	{
		g_foundBfLCS.push_back(subseq);
		return subseq.size();
	}

	// 같은 경우
	if (a[i] == b[j])
	{
		subseq.push_back({ i, j });
		return findLCS_bf(a, b, i + 1, j + 1, subseq);
	}

	// 이외의 경우
	return max(findLCS_bf(a, b, i + 1, j, subseq), findLCS_bf(a, b, i, j + 1, subseq));
}

void sort_unique_foundLSC()
{
	sort(begin(g_foundBfLCS), end(g_foundBfLCS), [](const auto& a, const auto& b) { 
		if (a.size() != b.size())
			return a.size() < b.size();

		return a < b; });

	g_foundBfLCS.erase(unique(begin(g_foundBfLCS), end(g_foundBfLCS)), end(g_foundBfLCS));
}

int main(void)
{
	string a("ABCX");
	string b("ACYXB");
	cout << findLCS_bf(a, b, 0, 0, {});
	sort_unique_foundLSC();

	return 0;
}