#include <iostream>
#include <iterator>
#include <vector>
#include <array>
#include <list>
#include <type_traits>

using namespace std;

namespace _internal
{
    template<typename _Ty, typename _Container>
    class ring_queue_traits
    {
    public:
        using container_type = _Container;
        using value_type = typename container_type::value_type;
        using size_type = typename container_type::size_type;
    };

    template<typename _Ty, class _Container, typename _IterCategory = typename _Container::iterator::iterator_category>
    class ring_queue_base;

    template<typename _Ty, typename _Container>
    class ring_queue_base<_Ty, _Container, std::random_access_iterator_tag>
        : public ring_queue_traits<_Ty, _Container>
    {
    public:
        ~ring_queue_base() = default;

        ring_queue_base(const size_type maxSize)
            : m_frontPos{ 0 }
            , m_backPos{ 1 }
            , m_currSize{ 0 }
            , m_datas(maxSize+1)
        {

        }

        ring_queue_base(const ring_queue_base& src)
            : m_frontPos{ src.m_frontPos }
            , m_backPos{ src.m_backPos }
            , m_currSize{ src.m_currSize }
            , m_datas{ src.m_datas }
        {

        }

        ring_queue_base(ring_queue_base&& src) noexcept
        {
            swap(src);
        }
        
        size_type size() const noexcept
        {
            return m_currSize;
        }

        size_type max_size() const noexcept
        {
            return m_datas.size();
        }

        bool empty() const noexcept
        {
            return m_currSize == 0;
        }

        bool full() const noexcept
        {
            return m_frontPos == m_backPos;
        }

        template<typename _Ty>
        bool push(_Ty&& v)
        {
            if (!full())
            {
                m_datas[m_backPos] = std::forward<_Ty>(v);
                
                m_backPos = ++m_backPos % m_datas.size();
                ++m_currSize;

                return true;
            }

            return false;
        }

        void pop() noexcept
        {
            if (!empty())
            {
                m_frontPos = ++m_frontPos % m_datas.size();
                m_datas[m_frontPos] = value_type{};
                --m_currSize;
            }
        }

        value_type& front() noexcept
        {
            return m_datas[(m_frontPos+1) % m_datas.size()];
        }

        template<typename _Ty>
        void swap(_Ty& rhs) noexcept
        {
            using std::swap;
            
            swap(m_frontPos, rhs.m_frontPos);
            swap(m_backPos, rhs.m_backPos);
            swap(m_currSize, rhs.m_currSize);
            swap(m_datas, rhs.m_datas);
        }

        template<typename _Ty>
        ring_queue_base& operator=(_Ty&& rhs)
        {
            ring_queue_base v{ std::forward<_Ty>(rhs) };
            this->swap(v);

            return *this;
        }

    private:
        size_type m_frontPos;
        size_type m_backPos;
        size_type m_currSize;
        container_type m_datas;
    };
}

int main(void)
{
    using namespace _internal;
    using namespace std;

    ring_queue_base<int, std::vector<int>> b1(3);
    b1.push(1);
    b1.push(2);
    b1.push(3);
    b1.push(4);
    b1.push(5);

    ring_queue_base<int, std::vector<int>> b2(5);
    b2.push(6);
    b2.push(7);
    b2.push(8);
    b2.push(9);
    b2.push(10);
   
    b1 = b2;
    while (!b1.empty())
    {
        cout << b1.front() << endl;
        b1.pop();
    }

    while (!b2.empty())
    {
        cout << b2.front() << endl;
        b2.pop();
    }

    return 0;
}