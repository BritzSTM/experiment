#include <iostream>
#include <vector>
#include <algorithm>

struct IClickListener
{
    virtual ~IClickListener() = default;
    virtual void click(const int someCode) = 0;

protected:
    IClickListener() = default;
    IClickListener(const IClickListener&) = default;
    IClickListener(IClickListener&&) noexcept = default;
};

class CSomeObserver
    : public IClickListener
{
public:
    virtual void click(const int someCode) override
    {
        std::cout << "code : " << someCode;
    }
};

class CClickSubject
{
public:
    void reg(IClickListener* pListener)
    {
        m_listeners.push_back(pListener);
    }

    void unreg(const IClickListener* const pListener)
    {
        using namespace std;

        auto iter{ find(begin(m_listeners), end(m_listeners), pListener) };
        if (iter != cend(m_listeners))
        {
            m_listeners.erase(iter);
        }
    }

    void notify(const int someCode)
    {
        for (auto& elem : m_listeners)
        {
            elem->click(someCode);
        }
    }

private:
    std::vector<IClickListener*> m_listeners;
};

int main(void)
{
    CClickSubject subject;
    CSomeObserver o;

    subject.reg(&o);
    subject.notify(10);

    subject.unreg(&o);
    subject.notify(20);

    return 0;
}