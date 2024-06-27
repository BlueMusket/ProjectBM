// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkCore.h"
#include "Async/AsyncWork.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "FlatHandler.h"

#if UE_EDITOR
PRAGMA_DISABLE_OPTIMIZATION
#endif

#define MAX_PACKET_SIZE 1024

typedef unsigned short PacketSize_t;
typedef unsigned short PacketId_t;
typedef unsigned char CompressType_t;
typedef unsigned char EncryptionType_t;

struct FPacketHeader
{
    PacketSize_t m_Size;
    PacketId_t m_Id;
    CompressType_t m_CompressType;
    EncryptionType_t m_EncryptionType;
};


class FRecvTask : public FNonAbandonableTask
{
public:
    FRecvTask(CNetworkCore* NewOwner, FSocket* NewSocket) : Socket(NewSocket), Owner(NewOwner) {}

    void DoWork()
    {
        CFlatHandler handler;
        uint8_t* buffer = handler.Pack();
        handler.UnPack(buffer);


        // 연결이 완료 될 때 까지 대기
        while (Owner->CheckRunning())
        {
            if (nullptr == Socket)
            {
                break;
            }

            ESocketConnectionState State = Socket->GetConnectionState();
            if (SCS_Connected == State)
            {
                break;
            }

            FPlatformProcess::Sleep(1.0f);
        }

        uint8* BufferHeader = new uint8[MAX_PACKET_SIZE];

        int LeftByte = 0;
        // recv 시작
        while (Owner->CheckRunning())
        {
            if (nullptr == Socket)
            {
                break;
            }

            uint32 Size;

            while (Socket->HasPendingData(Size))
            {
                int32 ReadByte = 0;
                Socket->Recv(&BufferHeader[LeftByte], sizeof(BufferHeader) - LeftByte, ReadByte);

                int total = LeftByte + ReadByte;
                int handled = 0;

                uint8* Buffer = BufferHeader;

                // byte 처리
                while (handled < total)
                {
                    // FlatBuffer

                    LeftByte -= handled;
                }

                // byte 이동
                memmove(BufferHeader, BufferHeader + handled, total - handled);
			}
        }

        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);

        Owner->Shutdown();

        UE_LOG(LogTemp, Warning, TEXT("Async task completed"));
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FRecvTask, STATGROUP_ThreadPoolAsyncTasks);
    }

private:
    FSocket* Socket;
    CNetworkCore* Owner;
};


class FPingTask : public FNonAbandonableTask
{
public:
    FPingTask(CNetworkCore* NewOwner, FSocket* NewSocket) : Socket(NewSocket), Owner(NewOwner) {}

    void DoWork()
    {
        // 연결이 완료 될 때 까지 대기
        while (Owner->CheckRunning())
        {
            if (nullptr == Socket)
            {
                return;
            }

            ESocketConnectionState State = Socket->GetConnectionState();
            if (SCS_Connected == State)
            {
                break;
            }

            FPlatformProcess::Sleep(1.0f);
        }

        // 연결이 완료 될 때 까지 대기
        while (Owner->CheckRunning())
        {
            if (nullptr == Socket)
            {
                break;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Async task completed"));
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FPingTask, STATGROUP_ThreadPoolAsyncTasks);
    }


private:
    FSocket* Socket;
    CNetworkCore* Owner;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CNetworkCore* CNetworkCore::Get()
{
    static CNetworkCore* Instance = nullptr;

    if (!Instance)
    {
        Instance = new CNetworkCore();
    }
    return Instance;
}


CNetworkCore::CNetworkCore()
    : Socket(nullptr), IsConnected(false), IsRunning(false)
{
}

CNetworkCore::~CNetworkCore()
{
    SetRunning(false);
    Shutdown();
}

bool CNetworkCore::Connect(const FString& IPAddress, int32 Port)
{

    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

    FIPv4Address IP;
    FIPv4Address::Parse(IPAddress, IP);

    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);

    Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("default"), Addr->GetProtocolType());

    Socket->SetNonBlocking();

    (new FAutoDeleteAsyncTask<FRecvTask>(this, Socket))->StartBackgroundTask();
    (new FAutoDeleteAsyncTask<FPingTask>(this, Socket))->StartBackgroundTask();

    IsConnected = Socket->Connect(*Addr);

    if (IsConnected)
    {
        UE_LOG(LogTemp, Log, TEXT("Connected to server"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to connect to server"));
    }

    
    ESocketErrors LastError = SocketSubsystem->GetLastErrorCode();

    return IsConnected;
}

void CNetworkCore::Shutdown()
{
    if (Socket)
    {
        Socket = nullptr;
    }

    IsConnected = false;
}

bool CNetworkCore::Send(const TArray<uint8>& Data)
{
    if (!IsConnected || !Socket)
    {
        return false;
    }

    int32 BytesSent = 0;
    return Socket->Send(Data.GetData(), Data.Num(), BytesSent);
}