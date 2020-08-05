#include <iostream>
#include <variant>
#include <type_traits>
#include <vector>

using namespace std;

using var_t = variant<int, long, double, std::string>;

template<class... _Ts>
struct overloaded : _Ts...
{
    using _Ts::operator()...;
};

template<class... _Ts> 
overloaded(_Ts...) -> overloaded<_Ts...>;


int main(void)
{
    vector<var_t> vec = { 10, 15l, 1.5, "hello" };

    for (auto& v : vec) {
        std::visit(overloaded{
            [](auto arg) { std::cout << arg << ' '; },
            [](double arg) { std::cout << std::fixed << arg << ' '; },
            [](const std::string& arg) { std::cout << arg << ' '; },
            }, v);
    }

    return 0;
}