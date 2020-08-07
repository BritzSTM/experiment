#include <iostream>
#include <fstream>

#define CONCAT_IMPL(s1, s2) s1##s2
#define CONCAT(s1, s2) CONCAT_IMPL(s1, s2)

#ifdef __COUNTER__
#   define AN_VAR(str) CONCAT(str, __COUNTER__)

#else
#   define AN_VAR(str) CONCAT(str, __LINE__)

#endif

namespace _internal
{
    class UncaughtExceptionCounter
    {
    public:
        UncaughtExceptionCounter()
            : m_exceptionCnt{ std::uncaught_exceptions() }
        {

        }

        bool newUncaughtException() noexcept
        {
            return std::uncaught_exceptions() > m_exceptionCnt;
        }

    private:
        int getUncaughtExceptionCount() const noexcept 
        {
            return m_exceptionCnt;
        }

    private:
        int m_exceptionCnt;
    };

    template<typename FnType, bool executeOnException>
    class ScopeGuardForNewException
    {
    public:
        // 형에 따라 예외가 발생할 수 있음
        ~ScopeGuardForNewException() noexcept(executeOnException)
        {
            if (executeOnException == m_ec.newUncaughtException())
            {
                m_fn();
            }
        }

        template<typename _Fn>
        explicit ScopeGuardForNewException(_Fn&& fn)
            : m_fn{std::forward<_Fn>(fn)}
        {

        }

    private:
        FnType m_fn;
        UncaughtExceptionCounter m_ec;
    };

    enum class ScopeGuardOnFail {};
    
    template<typename _FnType>
    ScopeGuardForNewException<typename std::decay<_FnType>::type, true>
        operator+(ScopeGuardOnFail, _FnType&& fn)
    {
        return ScopeGuardForNewException<typename std::decay<_FnType>::type, true>(std::forward<_FnType>(fn));
    }

    enum class ScopeGuardOnExit {};

    template<typename _Func>
    class ScopeGuard final
    {
    public:
        ~ScopeGuard()
        {
            m_fn();
        }

        template<typename _Func>
        explicit ScopeGuard(_Func&& fn)
            : m_fn{std::forward<_Func>(fn)}
        {

        }

    private:
        _Func m_fn;
    };

    template<typename _Func>
    ScopeGuard<_Func> operator+(ScopeGuardOnExit, _Func&& fn)
    {
        // todo
        return ScopeGuard<_Func>(std::forward<_Func>(fn));
    }

}

#define SCOPE_EXIT \
    auto AN_VAR(SCOPE_EXIT_STATE) \
    = ::_internal::ScopeGuardOnExit() + [&]()

#define SCOPE_FAIL \
    auto AN_VAR(SCOPE_FAIL_STATE) \
    = ::_internal::ScopeGuardOnFail() + [&]() noexcept

// not working
void fn1()
{
    const char name[] = "/tmp/some.ext";

    std::ifstream stream;
    SCOPE_EXIT{ stream.close(); };

    // todo...
}

int main(void)
{
    return 0;
}