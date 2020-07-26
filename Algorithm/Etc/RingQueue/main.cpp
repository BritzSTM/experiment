#include <iostream>
#include <vector>
#include <array>

using namespace std;

namespace _internal
{
    template<typename _Ty, typename _Container>
    class ring_queue_base
    {
    public:
        using container_type = _Container;
        using value_type = typename container_type::value_type;
        using size_type = typename container_type::size_type;        

    public:
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        size_type resize(const size_type n);
        bool empty() const noexcept;

        void swap(ring_queue_base& v);
        void assign(const ring_queue_base& v);

    private:
        container_type m_datas;
    };

    // list, vector, array
    template<typename _Ty, typename _Container>
    class ring_deque
        : public ring_queue_base<_Ty, _Container>
    {
    public:
        ring_deque(const size_type n);
        ring_deque(const ring_deque& rdq);
        ring_deque(ring_deque&& rdq) noexcept;

        template<typename _Ty>
        bool front_push(_Ty && v);
        void front_pop();
        value_type& front();

        template<typename _Ty>
        bool back_push(_Ty&& v);
        void back_pop();
        value_type& back();

        template<typename _RingQueue>
        ring_deque& operator=(_RingQueue&& rdq);
    };

}

int main(void)
{

    return 0;
}