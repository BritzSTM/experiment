#include <iostream>
#include <type_traits>

template<typename _Ty>
struct CalleeTypeSimbol
{
    using Type = _Ty;
};

template<typename _Res, typename ..._Args>
struct SInvokerVT final
{
    /*
        Closure는 class layout을 가지는 것에 유의.
        함수 포인터도 지원해야 함.

        invoke, copy_ctor, destructor의 포인터타입 필요
    */
    using StoragePtrType = void*;

    using InvokePtrType = _Res(*)(StoragePtrType, _Args&& ...);
    using CopyPtrType = void(*)(StoragePtrType, StoragePtrType);
    using DestructorPtrType = void(*)(StoragePtrType);

    ~SInvokerVT() = default;

    explicit SInvokerVT() noexcept
        : invokePtr{
        static_cast<InvokePtrType>(
            [](StoragePtrType, _Args&&...) -> _Res
            {
                throw std::bad_function_call();
            }) }
        , copyPtr{
                static_cast<CopyPtrType>(
                    [](StoragePtrType, StoragePtrType) -> void
                    {}) }
                , destructorPtr{
                static_cast<DestructorPtrType>(
                    [](StoragePtrType) -> void
                    {}) }
                , calleeTypeSize{ 0 }
            {
                //this is ctor body. do not anything.
            }

            template<typename _F>
            explicit SInvokerVT(CalleeTypeSimbol<_F>) noexcept
                : invokePtr
            {
                static_cast<InvokePtrType>(
                    [](StoragePtrType storagePtr, _Args&&... args) -> _Res
                    {
                        return (*static_cast<_F*>(storagePtr))(std::forward<_Args>(args)...);
                    })
            }
                , copyPtr
                    {
                        static_cast<CopyPtrType>(
                            [](StoragePtrType destPtr, StoragePtrType srcPtr) -> void
                            {
                                new (destPtr) _F{ (*static_cast<_F*>(srcPtr)) };
                            })
                    }
                        , destructorPtr
                            {
                                static_cast<DestructorPtrType>(
                                    [](StoragePtrType storagePtr) -> void
                                    {
                                        (static_cast<_F*>(storagePtr))->~_F();
                                    })
                            }
                                , calleeTypeSize{ sizeof(_F) }
                                    {
                                        //this is ctor body. do not anything.
                                    }


    // Members
    const InvokePtrType invokePtr;
    const CopyPtrType copyPtr;
    const DestructorPtrType destructorPtr;
    const size_t calleeTypeSize;
};

template<typename _Res, typename ..._Args>
static const SInvokerVT<_Res, _Args...> kEmptyInvokerVT{ };

template<typename _Res, typename ..._Args>
static const auto kEmptyInvokerVTPtr{ std::addressof(kEmptyInvokerVT<_Res, _Args...>) };

int main()
{

    return 0;
}