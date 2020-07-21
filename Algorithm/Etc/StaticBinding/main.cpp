#include <iostream>
#include <memory>

using namespace std;

template<typename _Child>
class CBase
{
public:
    void SomeInterface()
    {
        static_cast<_Child*>(this)->SomeFunc();
    }
};

class CPrint
    : public CBase<CPrint>
{
public:
    // not virtual func 
    void SomeFunc()
    {
        cout << "Static binding call";
    }
};

int main(void)
{
    unique_ptr<CPrint> pPrint{ make_unique<CPrint>() };

    pPrint->SomeInterface();

    return 0;
}