/*
    https://programmers.co.kr/learn/courses/30/lessons/60057
*/
// 주어진 위치에서 연속으로 일치하는 블록 수를 반환
int getCompressInterval(const string& block, const string& target, const int targetPos)
{
    const int bkSize = block.size();
    int bkCnt{ 0 }, bkPos{ 0 };

    auto tIter = target.begin() + targetPos;

    while (tIter != target.end())
    {
        if (block[bkPos] == *tIter)
        {
            ++tIter;
            if (++bkPos == bkSize)
            {
                bkPos = 0;
                ++bkCnt;
            }
        }
        else
        {
            break;
        }
    }

    return bkCnt;
}

int compress(const int cutSize, const string& target)
{
    stringstream s;

    //컷 사이즈만큼 반복
    int skip{ 0 };
    while (skip < target.size())
    {
        string block{ target.substr(skip, cutSize) };
        int skipAble = getCompressInterval(block, target, skip);

        if (skipAble > 1)
        {
            s << skipAble << block;
            skip += (skipAble * cutSize);
        }
        else
        {
            s << block;
            skip += cutSize;
        }
    }

    //cout << cutSize << " " << s.str() << " " << s.str().size() << endl;
    return s.str().size();
}

int solution(string s) {
    int answer = 0;
    int minSize{ static_cast<int>(s.size()) };

    //컷 기준을 늘려가며 최소값을 획득한다.
    //단 문자열 길이의 반만큼이 한계
    for (int i{ 1 }; i <= (s.size() / 2); ++i)
    {
        minSize = min(minSize, compress(i, s));
    }

    answer = minSize;
    return answer;
}