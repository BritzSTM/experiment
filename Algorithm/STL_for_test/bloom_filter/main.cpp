/*
    0. 실제 데이터를 소유하지 않음!
    1. 거짓 부정은 없으나 거짓 긍정은 존재하는 것에 주의
    2. 3개 이상의 해쉬 함수를 사용해야 정확도가 높아짐
*/
#include <iostream>
#include <vector>


using namespace std;


class CBloomfilter
{
public:
    CBloomfilter(const int bitSize)
        : m_bits(bitSize, false)
    {

    }

    bool lookup(const int key) const
    {
        return { m_bits[hash(0, key)] && m_bits[hash(1, key)] && m_bits[hash(2, key)] };
    }

    void insert(const int key)
    {
        m_bits[hash(0, key)] = true;
        m_bits[hash(1, key)] = true;
        m_bits[hash(2, key)] = true;
    }

private:
    // 간단한 해쉬 함수
    int hash(const int hasher, const int key) const
    {
        switch (hasher)
        {
        case 0: return key % m_bits.size();
        case 1: return (key / 7) % m_bits.size();
        case 2: return (key / 11) % m_bits.size();
        default:
            break;
        }

        return 0;
    }

private:
    vector<bool> m_bits;
};


int main(void)
{
    CBloomfilter bf(7);

    bf.insert(100);
    bf.insert(54);
    bf.insert(82);

    cout << boolalpha << bf.lookup(5) << endl;
    cout << boolalpha << bf.lookup(50) << endl;
    cout << boolalpha << bf.lookup(20) << endl;
    cout << boolalpha << bf.lookup(54) << endl;

    return 0;
}