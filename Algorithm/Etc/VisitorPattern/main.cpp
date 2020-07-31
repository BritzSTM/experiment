#include <iostream>
#include <memory>
#include <vector>

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

struct IModel
{
    virtual void accept(IVisitor* pVisitor) = 0;
};

class CModel1
    : public IModel
{
public:
    virtual void accept(IVisitor* pVisitor) override
    {
        pVisitor->visit(*this);
    }
};

class CModel2 
    : public IModel
{
public:
    virtual void accept(IVisitor* pVisitor) override
    {
        pVisitor->visit(*this);
    }
};

int main(void)
{
    vector<unique_ptr<IModel>> models;
    models.emplace_back(new CModel1());
    models.emplace_back(new CModel2());

    auto pVisitor = make_unique<CVisitor>();
    for (auto& model : models)
    {
        model->accept(pVisitor.get());
    }

    return 0;
}