#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


template<typename _Iter, typename _DestIter, typename _Comp>
void merge(_Iter first1, _Iter last1, _Iter first2, _Iter last2, _DestIter dest, _Comp comp)
{
	while (first1 != last1 && first2 != last2)
	{
		if (comp(*first1, *first2))
		{
			dest = *first1;
			advance(first1, 1);
		}
		else
		{
			dest = *first2;
			advance(first2, 1);
		}
	}

	while (first1 != last1)
	{
		dest = *first1;
		advance(first1, 1);
	}

	while (first2 != last2)
	{
		dest = *first2;
		advance(first2, 1);
	}
}

template<typename _Container, typename _Comp, typename _Iter = _Container::iterator>
void merge_sort(_Container& data, _Iter first, _Iter last, _Comp comp)
{
	if (distance(first, last) <= 1)
		return;

	const auto mid{ floor(distance(first, last) / 2ull) };
	auto midIt{ first + mid };

	merge_sort(data, first, midIt, comp);
	merge_sort(data, midIt, last, comp);

	_Container tmp;
	tmp.reserve(distance(first, last));

	merge(first, midIt, midIt, last, std::back_inserter(tmp), comp);
	copy(cbegin(tmp), cend(tmp), first);

	return;
}


int main(void)
{
	vector<int> vec{ 55, 23, 11, 1, 0, 99, 88, 108, -44, -10};
	copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
	cout << endl;

	merge_sort(vec, vec.begin(), vec.end(), std::less<int>());
	copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
	cout << endl;

	merge_sort(vec, vec.begin(), vec.end(), std::greater<int>());
	copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}