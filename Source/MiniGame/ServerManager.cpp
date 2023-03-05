

#include "ServerManager.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "UserManager.h"
#include "MiniGameCharacter.h"


ServerManager::ServerManager()
    :m_buf(), m_previousPacketSize(0), character(nullptr), character2(nullptr), character3(nullptr)
{
}

ServerManager::~ServerManager()
{
}

void ServerManager::Initialize()
{
}

bool ServerManager::ConnectToServer()
{
	/// ������ connect ��û
	m_socket = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateSocket( NAME_Stream, TEXT( "default" ) );
    if (!m_socket)
    {
        return false;
    }

	FIPv4Address ip;
	if ( !FIPv4Address::Parse( SERVERIP, ip ) )
    {
        return false;
    }

	TSharedRef<FInternetAddr> address = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateInternetAddr();
	address->SetIp( ip.Value );
	address->SetPort( SERVERPORT );

	bool connect = m_socket->Connect( *address );

	if ( !connect )
    {
        return false;
    }

	m_socket->SetNonBlocking( true );
	m_socket->SetNoDelay( true );

    return true;
}

void ServerManager::ShutDown()
{
    if (m_socket)
    {
        m_socket->Close();
    }
}
// 10 7 7
void ServerManager::RecvPacket()
{
    if ( !m_socket )
        return;

    char buf2[InitPacket::MAX_BUFFERSIZE];
    char* packet = m_buf;
    int32 bytesSents = 0;
    int32 packetSize = 0;
    bool initCome = true;

    bool returnValue = m_socket->Recv((uint8*)(buf2), InitPacket::MAX_BUFFERSIZE - 1, bytesSents);
    if ( !returnValue )
    {
        return;
    }
    // ���� ������ ����
    else if ( bytesSents == 0 )
    {
        return;
    }

    // ������ �޾Ҵ� ��Ŷ�� ���� ��� �� �ڿ�, ������ �޾Ҵ� ��Ŷ�� ������ m_previousPacketSize �� 0
    memcpy_s(m_buf + m_previousPacketSize, sizeof(m_buf), buf2, sizeof(buf2));

    do
    {
        // �޾ƿ� ������
        packetSize = packet[0];
        
        // �޾ƿ� ��Ŷ ������ ũ�⺸�� ���� �����Ͱ� ���� ��� -> ��Ŷ�� �����ؼ� ProcessPacket ����
        if (packetSize <= bytesSents)
        {
            char assemble[InitPacket::MAX_BUFFERSIZE] = { NULL, };
            memcpy_s(assemble, sizeof(assemble), m_buf, packetSize);
            ProcessPacket(assemble);

            packet += packetSize;
            bytesSents -= packetSize;
            m_previousPacketSize = 0;

            if (bytesSents != 0)
                memcpy_s(m_buf, sizeof(m_buf), packet, bytesSents);
            else
                ZeroMemory(m_buf, sizeof(m_buf));
        }
        // ��Ŷ ������ ũ�Ⱑ ���� �����ͺ��� ���� -> ��Ŷ�� �� �޾ƾ� ��
        else
        {
            packet += bytesSents;
            m_previousPacketSize = bytesSents;
        }
    } while (bytesSents > 0);
}

void ServerManager::SendPacket( char datainfo, void* packet )
{
    if ( packet == nullptr )
        return;

    switch ( datainfo )
    {
    case ClientToServer::LOGIN_REQUEST:
    {
        Packet::LoginRequest p = *( Packet::LoginRequest* )( packet );
        int32 bytesSents = 0;
        m_socket->Send( ( uint8* )( packet ), sizeof( p ), bytesSents );
    }
    break;
    case ClientToServer::MOVE:
    {

    }
    break;
    default:
        break;
    }
}

void ServerManager::ProcessPacket( char* packet )
{
    if ( !packet )
        return;

    switch ( packet[ 1 ] )
    {
    case ServerToClient::FIRSTINFO:
    {
        Packet::FirstPlayer p = *reinterpret_cast<Packet::FirstPlayer*> (packet);
        p.owner;

        if (character == nullptr)
            break;

        UserManager::GetInstance().PushPlayer(p.owner, character);
        
    }
    break;
    case ServerToClient::LOGON_OK:
    {
        Packet::LoginResult p = *reinterpret_cast< Packet::LoginResult* > ( packet );
        
    }
    break;
    case ServerToClient::LOGON_FAILED:
    {
        Packet::LoginResult p = *reinterpret_cast< Packet::LoginResult* > ( packet );

    }
    case ServerToClient::GAMESTART:
    {
  
        Packet::GameStart p = *reinterpret_cast< Packet::GameStart* > ( packet );
        int32 num = UserManager::GetInstance().GetPlayerMap().Num();

        if (UserManager::GetInstance().GetPlayerMap().Find(p.owner))
            break;

        if (num == 1)
        {
            UserManager::GetInstance().PushPlayer(p.owner, character2);
        }
        else if(num == 2)
        {
            UserManager::GetInstance().PushPlayer(p.owner, character3);
        }
      
    }
    break;
    case ServerToClient::MOVE:
    {
        Packet::Move p = *reinterpret_cast< Packet::Move* > ( packet );
    }
    break;
    default:
        break;
    }

}
