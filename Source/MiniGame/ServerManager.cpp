

#include "ServerManager.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "UserManager.h"
#include "MiniGameCharacter.h"


ServerManager::ServerManager()
    :m_buf(), m_previousPacketSize(0), m_Character(nullptr), m_Character2(nullptr), m_Character3(nullptr), m_bGameStart(false)
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
    // 받은 데이터 없음
    else if ( bytesSents == 0 )
    {
        return;
    }

    // 이전에 받았던 패킷이 있을 경우 그 뒤에, 이전에 받았던 패킷이 없으면 m_previousPacketSize 는 0
    memcpy_s(m_buf + m_previousPacketSize, sizeof(m_buf), buf2, sizeof(buf2));

    do
    {
        // 받아올 데이터
        packetSize = packet[0];
        
        // 받아올 패킷 데이터 크기보다 받은 데이터가 많을 경우 -> 패킷을 조립해서 ProcessPacket 수행
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
        // 패킷 데이터 크기가 받은 데이터보다 많음 -> 패킷을 더 받아야 함
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
        Packet::Move p = *(Packet::Move*)( packet );
        int32 bytesSents = 0;
        m_socket->Send( (uint8*)( packet ), sizeof( p ), bytesSents );
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

        if ( m_Character == nullptr )
            break;

        UserManager::GetInstance().PushPlayer(p.owner, m_Character);
        
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
        int32 playerMapSize = UserManager::GetInstance().GetPlayerMap().Num();

        // 객체 p가 담고있는 정보가 현재 플레이어에 대한 정보라면
        if ( UserManager::GetInstance().GetPlayerMap().Find( p.owner ) )
        {
            // 현재 플레이어에 대한 정보 할당
            UserManager::GetInstance().SetPlayerDefaultInfo( p.owner, p.x, p.y, p.color );
            UserManager::GetInstance().SetMainCharacterIndex( p.owner );

            break;
        }
        else // 객체 p가 담고있는 정보가 현재 플레이어에 대한 정보가 아니라면
        {
            // 다른 캐릭터에 대한 정보들 할당
            SetOtherCharacterStartInfo( p, playerMapSize );
        }     
    }
    break;
    case ServerToClient::MOVE:
    {
        Packet::Move p = *reinterpret_cast< Packet::Move* > ( packet );

        if ( UserManager::GetInstance().GetPlayerMap().Find( p.owner ) == nullptr )
        {
            return;
        }

        // 나를 제외한 플레이어의 캐릭터들의 움직임에 대한 정보 세팅
        SetCharacterMoveInfo( p );
    }
    break;
    default:
        break;
    }

}

// 현재 플레이어가 아닌 다른 플레이어 캐릭터들에 대한 정보 할당
void ServerManager::SetOtherCharacterStartInfo( Packet::GameStart& p, int playerMapSize )
{
    if ( playerMapSize == 1 )
    {
        UserManager::GetInstance().PushPlayer( p.owner, m_Character2 );
    }
    else if ( playerMapSize == 2 )
    {
        UserManager::GetInstance().PushPlayer( p.owner, m_Character3 );
        m_bGameStart = true;
    }

    UserManager::GetInstance().SetPlayerDefaultInfo( p.owner, p.x, p.y, p.color );
}

// 나를 제외한 플레이어의 캐릭터들의 움직임에 대한 정보 세팅 함수
void ServerManager::SetCharacterMoveInfo( Packet::Move& p )
{
    // 캐릭터의 시작 위치 정보와 목표 위치 정보 할당
    FVector tempLocation = FVector( p.x, p.y, UserManager::GetInstance().GetPlayerMap()[ p.owner ]->GetActorLocation().Z );
    UserManager::GetInstance().GetPlayerMap()[ p.owner ]->SetStartLocation( UserManager::GetInstance().GetPlayerMap()[ p.owner ]->GetActorLocation() );
    UserManager::GetInstance().GetPlayerMap()[ p.owner ]->SetTargetLocation( tempLocation );

    // 캐릭터가 현재 향하고 있는 방향 정보 할당
    FVector tempDirection = FVector( p.directionX, p.directionY, UserManager::GetInstance().GetPlayerMap()[ p.owner ]->GetActorForwardVector().Z );
    UserManager::GetInstance().GetPlayerMap()[ p.owner ]->SetTargetDirection( tempDirection );

    // 서버로부터 캐릭터의 움직임 정보를 받을지 말지의 대한 여부를 나타내는 플래그 변수에 true 값 할당
    UserManager::GetInstance().GetPlayerMap()[ p.owner ]->SetbRecvLocation( true );
}

