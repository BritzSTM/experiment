#include <iostream>
#include <algorithm>
#include <vector>
#include <random>


using namespace std;

vector<int> CreateNumbers(const size_t n)
{
	vector<int> res;
	res.reserve(n);

	random_device rd;
	mt19937 device(rd());
	uniform_int_distribution<int> db(-50, 50);

	for (auto i{ 0 }; i < n; ++i)
		res.push_back(db(device));

	return res;
}

inline void print(vector<int>& vec)
{
	copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
	cout << endl << endl;
}

// [first, last)
template<typename _Container, typename _Iter, typename _Pred>
void partition_sort(_Container& data, _Iter first, _Iter last, _Iter pivot, _Pred pred)
{
	if (distance(first, last) <= 1)
		return;

	auto pivotVal{ *std::next(first, std::distance(first, last) / 2) };
	auto newPivot1{ std::partition(first, last, [&pivotVal, &pred](const auto& em) { return pred(em, pivotVal); }) };
	auto newPivot2{ std::partition(newPivot1, last, [&pivotVal, &pred](const auto& em) { return !pred(pivotVal, em); }) }; // 피봇값과 같은 값에 대한 처리를 위해 한번 더 진행

	const auto targetDist{ distance(first, pivot) };

	partition_sort(data, first, newPivot1, pivot, pred);

	if (distance(first, newPivot1) < targetDist)
		partition_sort(data, newPivot1 + 1, last, pivot, pred);

	return;
}

int main(void)
{
	vector<int> vec{CreateNumbers(9)};
	print(vec);	

	cout << "old [4] " << *(vec.begin() + 4) << endl;
	partition_sort(vec, vec.begin(), vec.end(), vec.begin() + 4, less<int>());
	cout << "new [4] " << *(vec.begin() + 4) << endl;
	print(vec);

	cout << "old [4] " << *(vec.begin() + 4) << endl;
	partition_sort(vec, vec.begin(), vec.end(), vec.begin() + 4, greater<int>());
	cout << "new [4] " << *(vec.begin() + 4) << endl;
	print(vec);

	return 0;
}