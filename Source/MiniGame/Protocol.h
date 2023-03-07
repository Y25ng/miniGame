#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "InitDefine.h"

// PACKET DECLARE
#pragma pack(push, 1)
struct PacketInfo
{
	/*const*/ unsigned char	size;
	/*const*/ unsigned char type;

public:
	PacketInfo() = default;

	PacketInfo(
		const unsigned char	size,
		const unsigned char type )
		: size( size )
		, type( type ) {}
};
namespace Packet
{
	// 클라이언트 첫 접속 시 본인의 고유 인덱스 전송
	// 클라이언트에서는 해당 패킷을 받고 owner를 본인이 조작할 플레이어에 Set
	struct FirstPlayer
	{
		//const PacketInfo info;
		PacketInfo info;
		int owner;

		FirstPlayer( const int owner )
			: info( sizeof( FirstPlayer ), ServerToClient::FIRSTINFO )
			, owner( owner ) {}
	};

	// 로그인 요청
	// 클라이언트에서는 해당 패킷을 통해 로그인 요청을 전송
	struct LoginRequest
	{
		PacketInfo info;
		char name[ InitPlayer::MAX_NAME ];
		char password[ InitPlayer::MAX_PASSWORD ];
		int owner;

		LoginRequest( const int owner )
			: info( sizeof( LoginRequest ), ClientToServer::LOGIN_REQUEST )
			, owner( owner ), name(), password() {}
	};
	// 로그인 결과
	// 서버에서 로그인 결과를 클라이언트에게 전송 -> 패킷 타입이 Login Failed, LoginOk 중 하나
	// 패킷 타입(info.type)이 LoginOk면 닉네임 클라이언트 본인의 플레이어에 Set
	// LoginFailed면 로그인 실패 문구 출력.
	struct LoginResult
	{
		PacketInfo info;
		char name[ InitPlayer::MAX_NAME ];
		int owner;

		// 승률도 추가될 수 잇음
		LoginResult( const int owner, const int type/*Login Failed, Login Ok*/ )
			: info( sizeof( LoginResult ), type )
			, owner( owner ), name() {}
	};

	// 서버에서 미니게임 씬 전환 요청 및 초기화 정보 전송
	// 클라이언트에서 해당 패킷을 받고 플레이어들의 초기 위치, 고유 색상을 Set
	// owner를 통해 각 플레이어들을 구분할 것
	struct InitPlayers
	{
		PacketInfo info;
		int owner;			/* 플레이어 구분, 로그인 구현 시 추후 닉네임으로 변경*/
		short color;		/* 플레이어 고유 색상 0 - red, 1 - blue, 2 - yellow*/
		float x;			/*x 좌표*/
		float y;			/*y 좌표*/
		float directionX;	/*X방향 각도*/
		float directionY;	/*Y방향 각도*/

		// 초기 위치 추가될 예정

		InitPlayers( const int owner )
			: info( sizeof( InitPlayers ), ServerToClient::INITPLAYERS )
			, owner( owner ), color(), x(), y(), directionX(), directionY() {}
	};

	// 클라이언트가 이동 패킷 서버에게 전송
	// 서버에서 위치 검증 후 다른 클라이언트 들에게 전송
	// 클라이언트는 해당 패킷이 왔을 경우 owner를 통해 어떤 플레이어의 정보인지 확인 후
	// 해당 플레이어의 위치, 방향, 속도를 보간하여 갱신
	struct Move
	{
		PacketInfo info;
		int owner;
		float speed;
		float x;
		float y;
		float directionX;
		float directionY;

		Move( const int owner, const int type/*ClientToServer::Move, ServerToClient::Move*/ )
			: info( sizeof( Move ), type )
			, owner( owner ), speed(), x(), y(), directionX(), directionY() {}
	};

	// 플레이어와 블록과의 충돌 발생 시 클라에게 패킷 전송
	struct CollisionTile
	{
		PacketInfo info;
		int owner;
		int tileIndex;

		CollisionTile( const int owner, const int tileIndex )
			:info( sizeof( CollisionTile ), ServerToClient::COLLISION_BLOCK ), owner( owner ), tileIndex( tileIndex ) {}
	};

	// 플레이어와 플레이어의 충돌 패킷
	// 충돌이 발생한 플레이어 배열을 클라이언트에게 전송
	// 클라이언트는 owners가 -1이 아닌 플레이어들을 lookVector의 반대 방향으로 일정 힘만큼 밀기
	struct CollisionPlayer
	{
		PacketInfo info;
		int owners[ 3 ];

		CollisionPlayer()
			:info( sizeof( CollisionPlayer ), ServerToClient::COLLISION_PLAYER ), owners{ -1,-1,-1 } {	}
	};

	// 플레이어와 벽과 충돌
	struct CollisionWall
	{
		PacketInfo info;
		int owner;
		unsigned char wallNum;

		CollisionWall( const int owner, const unsigned char wallNum )
			: info( sizeof( CollisionWall ), ServerToClient::COLLISION_WALL ), owner( owner ), wallNum( wallNum ) {}
	};

	// 서버가 클라이언트에게 보내는 인게임 타이머
	// 단위: 1초
	struct Timer
	{
		PacketInfo info;
		unsigned char time; /*초 단위*/
		Timer( unsigned char time )
			:info( sizeof( Timer ), ServerToClient::TIME ), time( time ) {}
	};

	// 플레이어 점수 패킷
	struct Score
	{
		PacketInfo info;
		int owner;
		unsigned char score;
		Score( const int owner, unsigned char score ) :info( sizeof( Score ), ServerToClient::PLAYERSCORE ), owner( owner ), score( score ) {}
	};

	//아이템 스폰 패킷
	// 해당 좌표에 해당 타입의 아이템 클라이언트에 생성
	struct ItemSpawn
	{
		PacketInfo info;
		unsigned char itemtype;
		float x;
		float y;
		ItemSpawn( float x, float y, unsigned char itemtype ) :info( sizeof( ItemSpawn ), ServerToClient::ITEMSPAWN ), x( x ), y( y ), itemtype( itemtype ) {}
	};
}
#pragma pack(pop)

#endif // !PROTOCOL_H