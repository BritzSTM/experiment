#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <cassert>

template<template<typename _Ty, typename _Alloc = std::allocator<_Ty>> class _Container = std::list>
class CDeferrendPool final
{
public:
    using decay_shared_ptr = std::shared_ptr<void>;
    using container_type = _Container<decay_shared_ptr>;
    using size_type = std::size_t;

public:
    CDeferrendPool() = default;
    CDeferrendPool(const CDeferrendPool&) = delete;
    CDeferrendPool(CDeferrendPool&&) noexcept = delete;

    ~CDeferrendPool()
    {
        decline();
    }
    
    void add(decay_shared_ptr p)
    {
        m_rawPool.push_back(p);
    }

    size_type decline()
    {
        size_type cnt{ 0 };

        for (auto iter{ m_rawPool.begin() }; iter != m_rawPool.cend();)
        {
            if ((*iter).use_count() == 1)
            {
                iter = m_rawPool.erase(iter);
                ++cnt;
            }
            else
            {
                ++iter;
            }
        }

        return cnt;
    }

    CDeferrendPool& operator=(const CDeferrendPool&) = delete;
    CDeferrendPool& operator=(CDeferrendPool&&) noexcept = delete;

private:
    container_type m_rawPool;
};

int main(void)
{
    using namespace std;

    CDeferrendPool<> pool;
    shared_ptr<int> p = make_shared<int>(10);

    pool.add(p);
    assert(pool.decline() == 0);

    p.reset();
    assert(pool.decline() == 1);

    return 0;
}