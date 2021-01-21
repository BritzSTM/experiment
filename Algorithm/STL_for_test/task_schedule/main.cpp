#include <iostream>
#include <algorithm>
#include <list>


using namespace std;

class CTaskInfo
{
private:
	friend ostream& operator<<(ostream&, const CTaskInfo&);

public:
	~CTaskInfo() = default;
	CTaskInfo(const int id, const int startTime, const int endTime)
		: m_id{id}
		, m_sTime{startTime}
		, m_eTime{endTime}
	{

	}

	bool IsOverlap(const CTaskInfo& task) const
	{
		return task.m_sTime < m_eTime;
	}

	bool operator<(const CTaskInfo& rhs)
	{
		return m_eTime < rhs.m_eTime;
	}

private:
	int m_id;
	int m_sTime;
	int m_eTime;
};

ostream& operator<<(ostream& os, const CTaskInfo& task)
{
	os << "[ID] " << task.m_id << " [S] " << task.m_sTime << " [E] " << task.m_eTime;
	return os;
}

list<CTaskInfo> buildTasks()
{
	list<CTaskInfo> tasks;
	tasks.push_back({ 1, 5, 9 });
	tasks.push_back({ 2, 6, 20 });
	tasks.push_back({ 3, 16, 19 });
	tasks.push_back({ 4, 7, 10 });
	tasks.push_back({ 5, 9, 19 });
	tasks.push_back({ 6, 10, 19 });
	tasks.push_back({ 7, 6, 12 });
	tasks.push_back({ 8, 2, 17 });
	tasks.push_back({ 9, 10, 13 });
	tasks.push_back({ 10, 4, 7 });

	return tasks;
}

void SchedulingByGreedy(list<CTaskInfo>& tasks)
{
	tasks.sort();

	auto it{ begin(tasks) };
	while (it != end(tasks))
	{
		auto nextIt{ next(it) };
		while(nextIt != end(tasks) && it->IsOverlap(*nextIt))
			nextIt = tasks.erase(nextIt);

		++it;
	}
}

int main(void)
{
	auto tasks{ buildTasks() };

	cout << "builded task" << endl;
	copy(cbegin(tasks), cend(tasks), ostream_iterator<CTaskInfo>(cout, "\n"));
	cout << endl;

	cout << "scheduling task" << endl;
	SchedulingByGreedy(tasks);
	copy(cbegin(tasks), cend(tasks), ostream_iterator<CTaskInfo>(cout, "\n"));
	cout << endl;

	return 0;
}