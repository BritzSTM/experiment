#include <iostream>
#include <memory>

using namespace std;

/*
    고전 상태패턴
*/
namespace _internal
{
    enum EConnState
    {
        None,
        Connected,
        Disconnect
    };

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
}

using _internal::CEndPoint;

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

    return 0;
}