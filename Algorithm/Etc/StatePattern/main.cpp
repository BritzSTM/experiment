#include <iostream>
#include <memory>
#include <tuple>
#include <variant>

using namespace std;

namespace _internal
{
    enum EConnState
    {
        None,
        Connected,
        Disconnect
    };

    // 고전 상태패턴
    inline namespace v1
    {
        struct SEndPointDesc final
        {
            EConnState currState;
        };

        struct IEndPointState
        {
        public:
            virtual void Connect(SEndPointDesc&) = 0;
            virtual void Disconnect(SEndPointDesc&) = 0;
            virtual void Send(SEndPointDesc&) = 0;
            virtual void Receive(SEndPointDesc&) = 0;
        };


        class CEndPointNone
            : public IEndPointState
        {
            virtual void Connect(SEndPointDesc& desc) override
            {
                cout << "Connected" << endl;
                desc.currState = EConnState::Connected;
            }

            virtual void Disconnect(SEndPointDesc&) override
            {
                cout << "Not available in the current state" << endl;
            }

            virtual void Send(SEndPointDesc&) override
            {
                cout << "Not available in the current state" << endl;
            }

            virtual void Receive(SEndPointDesc&) override
            {
                cout << "Not available in the current state" << endl;
            }
        };

        class CEndPointConnected
            : public IEndPointState
        {
            virtual void Connect(SEndPointDesc&) override
            {
                cout << "Not available in the current state" << endl;
            }

            virtual void Disconnect(SEndPointDesc& desc) override
            {
                cout << "Disconnect" << endl;
                desc.currState = EConnState::Disconnect;
            }

            virtual void Send(SEndPointDesc&) override
            {
                cout << "Send Data" << endl;
            }

            virtual void Receive(SEndPointDesc&) override
            {
                cout << "Recive Data" << endl;
            }
        };

        class CEndPointDisconnect
            : public IEndPointState
        {
            virtual void Connect(SEndPointDesc& desc) override
            {
                cout << "Connected" << endl;
                desc.currState = EConnState::Connected;
            }

            virtual void Disconnect(SEndPointDesc&) override
            {
                cout << "Not available in the current state" << endl;
            }

            virtual void Send(SEndPointDesc&) override
            {
                cout << "Not available in the current state" << endl;
            }

            virtual void Receive(SEndPointDesc&) override
            {
                cout << "Not available in the current state" << endl;
            }
        };


        class CEndPoint
        {
        public:
            CEndPoint()
                : m_desc{ EConnState::None }
                , m_pStates{ make_unique<CEndPointNone>(), make_unique<CEndPointConnected>(), make_unique<CEndPointDisconnect>() }
            {

            }

            void Connect()
            {
                m_pStates[m_desc.currState]->Connect(m_desc);
            }

            virtual void Disconnect()
            {
                m_pStates[m_desc.currState]->Disconnect(m_desc);
            }

            virtual void Send()
            {
                m_pStates[m_desc.currState]->Send(m_desc);
            }

            virtual void Receive()
            {
                m_pStates[m_desc.currState]->Receive(m_desc);
            }

        private:
            SEndPointDesc m_desc;
            unique_ptr<IEndPointState> m_pStates[3];
        };
    }

    // variant를 이용한 다른 방식의 상태패턴. cpp_ver >= 17
    namespace diff
    {
        template<typename... _States>
        class TStateMachine
        {
        public:
            TStateMachine()
                : m_states{}
                , m_pCurrState{&get<0>(m_states)}
            {

            }

            template<typename _State>
            void transTo()
            {
                m_pCurrState = &get<_State>(m_states);
            }

            template<typename _Event>
            void handle(const _Event& event)
            {
                auto passEventToState = [this, &event](auto ptr)
                {
                    ptr->handle(event).execute(*this);
                };

                visit(passEventToState, m_pCurrState);
            }

        private:
            tuple<_States...> m_states;
            variant<_States*...> m_pCurrState;
        };

        template<typename _State>
        struct TransTo
        {
            template<typename _Machine>
            void execute(_Machine& m)
            {
                m.template transTo<_State>();
            }
        };

        struct Nothing
        {
            template<typename _Machine>
            void execute(_Machine&) {}
        };

        struct OpenEvent {};
        struct CloseEvent {};

        struct ClosedState;
        struct OpenState;

        struct ClosedState
        {
            TransTo<OpenState> handle(const OpenEvent&) const
            {
                cout << "opening..." << endl;
                return {};
            }

            Nothing handle(const CloseEvent&) const
            {
                cout << "already closed" << endl;
                return {};
            }
        };

        struct OpenState
        {
            TransTo<ClosedState> handle(const CloseEvent&) const
            {
                cout << "closing..." << endl;
                return {};
            }

            Nothing handle(const OpenEvent&) const
            {
                cout << "already open" << endl;
                return {};
            }
        };

        using CDoor = TStateMachine<ClosedState, OpenState>;
    }
}

using _internal::CEndPoint;
using namespace _internal::diff;

int main(void)
{
    CEndPoint endPoint;

    endPoint.Send();
    endPoint.Disconnect();

    endPoint.Connect();
    endPoint.Send();
    endPoint.Receive();
    endPoint.Connect();
    endPoint.Disconnect();

    endPoint.Send();
    endPoint.Disconnect();

    cout << "\nanother\n" << endl;

    CDoor door;
    door.handle(OpenEvent{});
    door.handle(OpenEvent{});
    door.handle(CloseEvent{});
    door.handle(CloseEvent{});

    return 0;
}