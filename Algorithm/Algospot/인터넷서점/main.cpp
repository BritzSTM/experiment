/*
    https://www.algospot.com/judge/problem/read/BOOKSTORE#

    1. 책을 구매해야지 포인트가 쌓이고 그 다음 책을 구매할 때 포인트를 쓸 수 있다
*/
#include <iostream>
#include <limits>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>


using namespace std;


using BookPrice = pair<int, int>; //first = price, second = point
using BookRecode = vector<BookPrice>; //ERecodeType을 이용해 접근할 것
using StoreRecode = vector<BookRecode>;

// 가격에 포인트를 적용한 금액이 나온다
inline void usePoint(int& price, int& point)
{
    price -= point;

    if (price < 0)
    {
        point = price * -1;
        price = 0;
    }
    else
    {
        point = 0;
    }
}

int getMinimalPrice(StoreRecode& stores)
{
    for (auto& store : stores)
    {
        sort(begin(store), end(store),
            [](const BookPrice& lhs, const BookPrice& rhs) { return lhs.second > rhs.second; });
    }

    int minPrice{ numeric_limits<int>::max() };
    for (auto& store : stores)
    {
        int total{ 0 }, point{ 0 };

        for (const auto& bookPrice : store)
        {
            int price{ bookPrice.first };
            usePoint(price, point);

            total += price;
            point += bookPrice.second;
        }

        minPrice = min(minPrice, total);
    }

    return minPrice;
}

int main(void)
{
    ios::sync_with_stdio(false);

    int c{ 0 };
    cin >> c;

    vector<int> caseRes;
    while (c--)
    {
        int books{ 0 }, stores{ 0 };
        cin >> books >> stores;

        StoreRecode storeRecode(stores, BookRecode( books ));

        for (int i{ 0 }; i < books; ++i)
        {
            for (int j{ 0 }; j < stores; ++j)
            {   
                cin >> storeRecode[j][i].first >> storeRecode[j][i].second;
            }
        }

        caseRes.push_back(getMinimalPrice(storeRecode));
    }

    copy(begin(caseRes), end(caseRes), ostream_iterator<int>{ cout, "\n" });

    return 0;
}