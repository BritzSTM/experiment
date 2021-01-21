#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

class CItem
{
private:
	friend ostream& operator<<(ostream& os, const CItem& item);

public:
	~CItem() = default;

	CItem(const int weight, const double price)
		: m_weight{ weight }
		, m_price{ price }
		, m_valuePerUnitWeight{ price / static_cast<double>(weight) }
	{

	}

	bool operator>(const CItem& rhs) const
	{
		return m_valuePerUnitWeight > rhs.m_valuePerUnitWeight;
	}

	int GetWeight() const { return m_weight; }
	int GetPrice() const { return m_price; }
	double GetValuePerUW() const { return m_valuePerUnitWeight; }

private:
	int m_weight;
	double m_price;
	double m_valuePerUnitWeight;
};

ostream& operator<<(ostream& os, const CItem& item)
{
	os << "[w] " << item.m_weight << " [p] " << item.m_price << " [uw] " << item.m_valuePerUnitWeight;
	return os;
}

vector<CItem> fillBag(vector<CItem>& items, const int bagMaxWeight)
{
	vector<CItem> bag;
	bag.reserve(items.size());
	sort(begin(items), end(items), greater<CItem>());

	int currBagWeight{ 0 };
	auto cursor{ begin(items) };

	while (cursor != items.end() && currBagWeight < bagMaxWeight)
	{
		bag.push_back(*cursor);
		currBagWeight += cursor->GetWeight();
		++cursor;
	}

	if (bagMaxWeight < currBagWeight)
	{
		const auto dropWeight{ currBagWeight - bagMaxWeight };
		
		auto& endItem{ bag.back() };
		endItem = CItem(endItem.GetWeight() - dropWeight, endItem.GetPrice() - (endItem.GetValuePerUW() * dropWeight));
	}

	return bag;
}

int main(void)
{
	vector<CItem> items{ {1, 10}, {2, 7}, {5, 15}, {9, 10}, {2, 12}, {3, 11}, {4, 5} };

	cout << "Items" << endl;
	copy(cbegin(items), cend(items), ostream_iterator<CItem>(cout, "\n"));
	cout << endl;
	
	const auto bag{ fillBag(items, 7) };
	copy(cbegin(bag), cend(bag), ostream_iterator<CItem>(cout, "\n"));
	cout << endl;

	return 0;
}