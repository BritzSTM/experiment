#include <iostream>
#include <cstring>

// 미정의 행동을 사용함
bool isBigEndian_bad() noexcept
{
    int v{ 0x01 };

    char* pV = reinterpret_cast<char*>(&v);

    return pV[3] == 0x01;
}

/*
    위 함수와 비교했을 때 복제 함수를 사용해서 좋지 않은 구현으로 보이지만
    컴파일러 최적화를 통해 동일한 코드를 생성할 수 있으며
    미정의 행동을 사용하지 않았으므로 명확한 구현
*/
bool isBigEndian_good() noexcept
{
    int v{ 0x01 };
    char datas[4];

    std::memcpy(datas, &v, sizeof(datas));

    return datas[3] == 0x01;
}

int main(void)
{
    using namespace std;

    cout << boolalpha << isBigEndian_bad() << endl;
    cout << boolalpha << isBigEndian_good() << endl;

    return 0;
}