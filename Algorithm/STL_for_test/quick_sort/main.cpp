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
	cout << endl;
}

template<typename _Container, typename _Iter, typename _Pred>
_Iter partition(_Container& data, _Iter first, _Iter last, _Iter pivot, _Pred pred)
{
	// [f, l]
	while (true)
	{
		while (*first <= *pivot && distance(first, last) > 0)
			++first;

		while (*last > *pivot && distance(first, last) > 0)
			--last;

		if (first == last)
			break;
		else
			iter_swap(first, last);
	}

	if (*pivot > *last)
		iter_swap(pivot, last);

	return pivot;
}

template<typename _Container, typename _Iter, typename _Pred>
void quick_sort(_Container& data, _Iter first, _Iter last, _Pred pred)
{
	const auto dist{ distance(first, last) };

	if (dist <= 1)
		return;

	auto pivotIt{ partition(data, first + 1, last, first, pred) };

	quick_sort(data, first, pivotIt - 1, pred);
	quick_sort(data, pivotIt, last, pred);

	return;
}


int main(void)
{
	vector<int> vec{CreateNumbers(6)};
	print(vec);

	quick_sort(vec, vec.begin(), vec.end(), less<int>());
	print(vec);

	quick_sort(vec, vec.begin(), vec.end(), greater<int>());
	print(vec);

	return 0;
}