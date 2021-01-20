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

// [first, last)
template<typename _Container, typename _Iter, typename _Pred>
_Iter partition(_Container& data, _Iter first, _Iter last, _Iter pivot, _Pred pred)
{
	// range setup to [first, last]
	if (first == pivot)
		advance(first, 1);
	else
	{
		iter_swap(first, pivot);
		first = next(pivot);
	}
	--last;

	while (true)
	{
		while (pred(*first, *pivot) && distance(first, last) > 0) 
			++first;

		while (pred(*pivot, *last) && distance(first, last) > 0)
			--last;

		if (first == last)
			break;
		else
			iter_swap(first, last);
	}

	if (pred(*last, *pivot))
		iter_swap(last, pivot);

	return last;
}

// [first, last)
template<typename _Container, typename _Iter, typename _Pred>
void quick_sort(_Container& data, _Iter first, _Iter last, _Pred pred)
{
	if (distance(first, last) <= 1) 
		return;

	auto pivotIt{ partition(data, first, last, first, pred) };

	quick_sort(data, first, pivotIt, pred);
	quick_sort(data, pivotIt, last, pred);

	return;
}

int main(void)
{
	vector<int> vec{CreateNumbers(9)};
	print(vec);

	quick_sort(vec, vec.begin(), vec.end(), less<int>());
	print(vec);

	quick_sort(vec, vec.begin(), vec.end(), greater<int>());
	print(vec);

	return 0;
}