

#include "ServerManager.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Protocol.h"


ServerManager::~ServerManager()
{
    ShutDown();
}

void ServerManager::Initialize()
{
}

bool ServerManager::ConnectToServer()
{
	/// 서버에 connect 요청
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

void ServerManager::RecvPacket()
{
    if ( !m_socket )
        return;

    char buf[ InitPacket::MAX_BUFFERSIZE ] = { NULL, };
    char* packet = buf;
    int32 bytesSents = 0;
    int32 packetSize = 0;
    bool init_come = true;
    int32 leftData = 2;

    while ( leftData > 0 || init_come )
    {
        bool returnValue = m_socket->Recv( ( uint8* )( packet ), InitPacket::MAX_BUFFERSIZE - 1, bytesSents );
        if ( !returnValue )
        {
            return;
        }
        ///받은 데이터 없음
        else if ( bytesSents == 0 )
        {
            break;
        }

        if ( init_come )
        {
            leftData = buf[ 0 ] - bytesSents;
            packet += bytesSents;
            init_come = false;
        }
        else
        {
            leftData -= bytesSents;
            packet += bytesSents;
        }

        if (leftData == 0)
        {
            ProcessPacket(buf);
        }
    }
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
        
        int a = 1;
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
        p;

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
