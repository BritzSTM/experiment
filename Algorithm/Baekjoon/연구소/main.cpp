/*
    https://www.acmicpc.net/problem/14502

    시행착오
    1. 시뮬레이션을 위해서는 보드의 복제가 필요했으나 이를 사전에 고려하지 않아
       복제가 가능하도록 다시 작성함
*/
#include <iostream>
#include <array>

using namespace std;

constexpr int kMaxN{ 8 };
constexpr int kMaxM{ 8 };
constexpr int kMaxBuildWall{ 3 };

using Board = array<array<int, kMaxM>, kMaxN>;
Board g_board { };
Board g_boardVisitor { };

enum EBlock : int
{
    E_Empty = 0,
    E_Wall = 1,
    E_Virus = 2
};

int g_n{};
int g_m{};

int countEmpty(const Board& board) noexcept
{
    int acc{ 0 };
    for (int i{ 0 }; i < g_n; ++i)
    {
        for (int j{ 0 }; j < g_m; ++j)
        {
            if (board[i][j] == E_Empty)
            {
                ++acc;
            }
        }
    }

    return acc;
}

void printBoard(const Board& board) noexcept
{
    for (int i{ 0 }; i < g_n; ++i)
    {
        for (int j{ 0 }; j < g_m; ++j)
        {
            cout << board[i][j] << " ";
        }

        cout << endl;
    }
}

inline bool isOutOfRange(int y, int x)
{
    return (y < 0 || y >= g_n || x < 0 || x >= g_m);
}

bool infectAround(Board& board, int y, int x)
{
    bool once{ false };

    //상
    if (!isOutOfRange(y - 1, x) && board[y - 1][x] == E_Empty)
    {
        board[y - 1][x] = E_Virus;
        once = true;
    }
    //하
    if (!isOutOfRange(y + 1, x) && board[y + 1][x] == E_Empty)
    {
        board[y + 1][x] = E_Virus;
        once = true;
    }
    //좌
    if (!isOutOfRange(y, x + 1) && board[y][x + 1] == E_Empty)
    {
        board[y][x + 1] = E_Virus;
        once = true;
    }
    //우
    if (!isOutOfRange(y, x - 1) && board[y][x - 1] == E_Empty)
    {
        board[y][x - 1] = E_Virus;
        once = true;
    }

    return once;
}

// 바이러스 확산을 시뮬레이션 하고 비어있는 공간의 수를 반환한다
int simulateVirus(Board board)
{
    // 바이러스 확산 시뮬레이션을 한다
    bool finish{ false };

    while (!finish)
    {
        int infectionCount{ 0 };

        for (int i{ 0 }; i < g_n; ++i)
        {
            for (int j{ 0 }; j < g_m; ++j)
            {
                if (board[i][j] == E_Virus)
                {
                    if (infectAround(board, i, j))
                    {
                        ++infectionCount;
                    }
                }
            }
        }

        // 한번도 감염시키지 못했다면 종료 
        if (infectionCount == 0)
        {
            finish = true;
        }
    }

    // 여기에 도달했다면 빈공간의 숫자를 반환한다.
    return countEmpty(board);
}


// 벽이 완성되면 시뮬레이션을 돌리고 나온 값을 반환한다. 그리고 그 값중에 최대 값을 반환 한도록 해야한다 
int simulateWall(const int wallCount)
{
    //벽 3개를 다 썻으면 기저이다
    if (wallCount == kMaxBuildWall)
    {
        return simulateVirus(g_board);
    }
   
    // 방문하지 않은 빈 공간을 찾는다
    int x{ -1 }, y{ -1 };
    bool found{ false };

    for (int i{ 0 }; i < g_n; ++i)
    {
        for (int j{ 0 }; j < g_m; ++j)
        {
            if (g_board[i][j] == E_Empty && g_boardVisitor[i][j] == 0)
            {
                g_boardVisitor[i][j] = -1;
                x = j;
                y = i;         

                found = true;
                break;
            }
        }

        if (found)
        {
            break;
        }
    }

    if (y == -1 || x == -1)
    {
        return 0;
    }

    // 빈공간에 벽을 세웠을 경우, 안새웠을 경우를 만들어 시뮬한다
    // 그리고 그중에 큰 값을 반환 한다
    int res{ 0 };
    for (int i{ 0 }; i < 2; ++i)
    {
        res = max(res, simulateWall(i + wallCount));
        g_board[y][x] = E_Wall;
    }

    //방문 사실을 취소한다
    g_boardVisitor[y][x] = 0;
    g_board[y][x] = E_Empty;

    return res;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> g_n >> g_m;

    for (int i{ 0 }; i < g_n; ++i)
    {
        for (int j{ 0 }; j < g_m; ++j)
        {
            cin >> g_board[i][j];
        }
    }

    //모든 벽을 세우는 경우를 만들어야 한다.
    //모든 벽을 세우는 경우에서 벽이 완성된경우 시뮬레이션을 돌려야 한다.
    cout << simulateWall(0) << endl;

    return 0;
}