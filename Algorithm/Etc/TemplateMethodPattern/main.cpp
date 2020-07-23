#include <iostream>
#include <memory>

using namespace std;

class CCarModel
{
public:
    // No virtual func
    void DrawInfo() const noexcept
    {
        cout << "Car Name : " << getCarName() << endl;
        cout << "Car speed : " << getSpeed() << endl;
    }

private:
    virtual const char* getCarName() const noexcept = 0;
    virtual int getSpeed() const noexcept = 0;
};

class CDumpTruck
    : public CCarModel
{
private:
    virtual const char* getCarName() const noexcept
    {
        return "I'm truck";
    }

    virtual int getSpeed() const noexcept override
    {
        return 80;
    }
};

int main(void)
{
    unique_ptr<CCarModel> pTruck{ make_unique<CDumpTruck>() };
    pTruck->DrawInfo();

    return 0;
}