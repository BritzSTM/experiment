/*
    https://www.algospot.com/judge/problem/read/BOOKSTORE#

    저장방식 바꿔야함
    게산방식 바꿔야함
*/
#include <iostream>
#include <limits>
#include <array>
#include <vector>
#include <utility>


using namespace std;


enum ERecode
{
    ETotalVal,
    EMinVal
};

using BookPrice = pair<int, int>; //first = price, second = point
using BookRecode = array<BookPrice, 2>; //ERecodeType을 이용해 접근할 것
using StoreRecode = vector<BookRecode>;


void InitStoreRecode(StoreRecode& recode, int storeCount)
{
    //! 이미 레코드들이 생성되어 있어야함

    for (auto& bookRecode : recode)
    {
        bookRecode[ERecode::ETotalVal].first = bookRecode[ERecode::ETotalVal].second = 0;

        //최소 포인트를 가진 것을 획득해야 함. 따라서 포인트는 최대 값으로 설정
        bookRecode[ERecode::EMinVal].first = 0;
        bookRecode[ERecode::EMinVal].second = numeric_limits<int>::max();
    }
}

void renewBookRecode(BookRecode& recode, const BookPrice& price)
{
    //무조건 최종 금액에 우선 합산한다. 
    recode[ERecode::ETotalVal].first += price.first;
    recode[ERecode::ETotalVal].second += price.second;

    //만약 현재 가게의 지정된 최소 값보다 작다면 갱신
    if (recode[ERecode::EMinVal].second > price.second)
    {
        recode[ERecode::EMinVal].first = price.first;
        recode[ERecode::EMinVal].second = price.second;
    }
}

int getMinimalPrice(StoreRecode& stores)
{
    // 최종금액 = 최종 현금 액수 + 최종 포인트 + 최소 포인트(마지막 구매이므로 결제시 사용불가
    // 최종금액이 적은 가게를 선정 및 출력
    int total{ numeric_limits<int>::max() };

    for (auto& store : stores)
    {
        int finalVal{ store[ERecode::ETotalVal].first - store[ERecode::ETotalVal].second + store[ERecode::EMinVal].second };
        
        total = min(total, finalVal);
    }

    return total;
}

int main(void)
{
    ios::sync_with_stdio(false);

    int c{ 0 };
    cin >> c;

    while (c--)
    {
        int books{ 0 }, store{ 0 };
        cin >> books >> store;

        StoreRecode storeRecode(store);
        InitStoreRecode(storeRecode, store);

        for (int i{ 0 }; i < books; ++i)
        {
            for (int j{ 0 }; j < store; ++j)
            {
                BookPrice price{};
                cin >> price.first >> price.second;

                renewBookRecode(storeRecode[j], price);
            }
        }

        cout << getMinimalPrice(storeRecode) << endl;
    }

    return 0;
}