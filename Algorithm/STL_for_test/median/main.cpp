#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class CMedian
{
public:
	double get() const
	{
		if (m_maxHeap.size() == m_minHeap.size())
		{
			return (m_maxHeap.top() + m_minHeap.top()) / 2.0;
		}
		else if (m_maxHeap.size() < m_minHeap.size())
		{
			return m_minHeap.top();
		}
		
		return m_maxHeap.top();
	}

	void insert(const int val)
	{
		if (m_maxHeap.empty())
		{
			m_maxHeap.push(val);
			return;
		}

		if (m_maxHeap.size() == m_minHeap.size())
		{
			if (val <= get())
			{
				m_maxHeap.push(val);
			}
			else
			{
				m_minHeap.push(val);
			}

			return;
		}

		if (m_maxHeap.size() < m_minHeap.size())
		{
			if (val > get())
			{
				m_maxHeap.push(m_minHeap.top());
				m_minHeap.pop();
				m_minHeap.push(val);
			}
			else
			{
				m_maxHeap.push(val);
			}

			return;
		}

		if (val < get())
		{
			m_minHeap.push(m_maxHeap.top());
			m_maxHeap.pop();
			m_maxHeap.push(val);
		}
		else
		{
			m_minHeap.push(val);
		}

		return;
	}

private:
	priority_queue<int> m_maxHeap;
	priority_queue<int, vector<int>, greater<int>> m_minHeap;
};

int main(void)
{
	CMedian med;

	med.insert(1);
	cout << med.get() << endl;

	med.insert(5);
	cout << med.get() << endl;

	med.insert(2);
	cout << med.get() << endl;

	med.insert(10);
	cout << med.get() << endl;

	med.insert(40);
	cout << med.get() << endl;

	return 0;
}