#include <iostream>
#include <memory>

using namespace std;

class CModel1;
class CModel2;

struct IVisitor
{
    virtual void visit(CModel1&) = 0;
    virtual void visit(CModel2&) = 0;
};

class CVisitor final
    : public IVisitor
{
public:
    virtual void visit(CModel1&) override
    {
        cout << "Model1 visited" << endl;
    }

    virtual void visit(CModel2&) override
    {
        cout << "Model2 visited" << endl;
    }
};

class CModel1 { };
class CModel2 { };

int main(void)
{
    auto pVisitor = make_unique<CVisitor>();
    CModel1 m1;
    CModel2 m2;

    pVisitor->visit(m1);
    pVisitor->visit(m2);

    return 0;
}