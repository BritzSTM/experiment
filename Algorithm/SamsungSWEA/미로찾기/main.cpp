#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>

using namespace std;
using MazeBoard = vector<vector<int>>;

enum EMazeChip
{
    E_Wall = 1,
    E_Road = 0,
    E_Visit = 2
};

MazeBoard getMaze()
{
    // 열거형으로 맵을 표현하니가시성이 더 떨어져 보였음
    return
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 },
        { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
}

struct Point
{
    int y, x;

    Point operator+(const Point& rhs) 
    {
        return { y + rhs.y, x + rhs.x};
    }

    Point operator-(const Point& rhs)
    {
        return { y - rhs.y, x - rhs.x };
    }

    bool operator==(const Point& rhs)
    {
        return ((y == rhs.y) && (x == rhs.x));
    }
};

// 맵을 복제함. 방문을 표시하기 위해서. sp(시작점), fp(종료점)
bool findPath(const Point& sp, const Point& fp, MazeBoard board, vector<Point>& outPath)
{
    constexpr Point searchDir[4] {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // 상 우 하 좌
    constexpr int kMaxSearch{ 4 };

    bool found{ false };
    
    stack<Point> currPos;
    currPos.push(sp);
    outPath.push_back(sp);
    board[sp.y][sp.x] = E_Visit;

    while (!currPos.empty())
    {
        if (currPos.top() == fp)
        {
            found = true;
            break;
        }
        else
        {
            int i{ 0 };
            for (i = 0; i < kMaxSearch; ++i)
            {
                auto nextPos = currPos.top() + searchDir[i];
                
                if (board[nextPos.y][nextPos.x] == E_Road)
                {
                    currPos.push(nextPos);
                    board[nextPos.y][nextPos.x] = E_Visit;
                    break;
                }
            }

            // 사방이 갈곳이 없다
            if (i == kMaxSearch)
            {
                currPos.pop();
            }
        }
    }

    //찾은 경로 출력
    outPath.resize(currPos.size());
    for (auto iter{ rbegin(outPath) }; iter != rend(outPath); ++iter)
    {
        *iter = currPos.top();
        currPos.pop();
    }

    return found;
}

int main(void)
{
    const Point sp{ 1, 1 };
    const Point fp{ 9, 1 };
    auto maze = getMaze();
    vector<Point> foundPath;

    if (findPath(sp, fp, maze, foundPath))
    {
        for (const auto& p : foundPath)
        {
            cout << "(" << p.y << "," << p.x << ")" << endl;
        }
    }

    return 0;
}