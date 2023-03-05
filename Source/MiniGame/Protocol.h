

#ifndef PROTOCOL_H
#define PROTOCOL_H

namespace InitPacket
{
	constexpr unsigned short MAX_BUFFERSIZE = 1024;
	constexpr unsigned short MAX_PACKETSIZE = 255;
}

namespace InitPlayer
{
	constexpr int MAX_NAME = 16;
	constexpr int MAX_PASSWORD = 32;
	constexpr float INITPOSITION_X = -1777.f;
	constexpr float INITINTERVAL = 1080.f;
}

namespace InitWord
{
	constexpr float BOX_SIZE = 32.f;
}
// PACKET TYPE

// CLIENT
namespace ClientToServer
{
	constexpr short LOGIN_REQUEST = 0;
	constexpr short MOVE = 1;
}
// SERVER
namespace ServerToClient
{
	constexpr short FIRSTINFO = -1;
	constexpr short LOGON_OK = 0;
	constexpr short LOGON_FAILED = 1;
	constexpr short GAMESTART = 2;
	constexpr short MOVE = 3;
}

// PACKET DECLARE
#pragma pack(push, 1)
struct PacketInfo
{
	/*const*/ unsigned char	 size;
	/*const*/ short type;

public:
	PacketInfo() = default;

	PacketInfo(
		const unsigned char	 size,
		const unsigned short type)
		: size(size)
		, type(type)
	{
	}
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

		FirstPlayer(const int owner)
			: info(sizeof(FirstPlayer), ServerToClient::FIRSTINFO)
			, owner(owner)
		{}
	};

	// 로그인 요청
	// 클라이언트에서는 해당 패킷을 통해 로그인 요청을 전송
	struct LoginRequest
	{
		PacketInfo info;
		char name[InitPlayer::MAX_NAME];
		char password[InitPlayer::MAX_PASSWORD];
		int owner;

		LoginRequest(const int owner)
			: info(sizeof(LoginRequest), ClientToServer::LOGIN_REQUEST)
			, owner(owner), name(), password()
		{}
	};
	// 로그인 결과
	// 서버에서 로그인 결과를 클라이언트에게 전송 -> 패킷 타입이 Login Failed, LoginOk 중 하나
	// 패킷 타입(info.type)이 LoginOk면 닉네임 클라이언트 본인의 플레이어에 Set
	// LoginFailed면 로그인 실패 문구 출력.
	struct LoginResult
	{
		PacketInfo info;
		char name[InitPlayer::MAX_NAME];
		int owner;

		// 승률도 추가될 수 잇음
		LoginResult(const int owner, const int type/*Login Failed, Login Ok*/)
			: info(sizeof(LoginResult), type)
			, owner(owner), name()
		{}
	};

	// 서버에서 미니게임 씬 전환 요청 및 초기화 정보 전송
	// 클라이언트에서 해당 패킷을 받고 플레이어들의 초기 위치, 고유 색상을 Set
	// owner를 통해 각 플레이어들을 구분할 것
	struct GameStart
	{
		PacketInfo info;
		int owner; /* 플레이어 구분, 로그인 구현 시 추후 닉네임으로 변경*/
		short color; /* 플레이어 고유 색상 0 - red, 1 - blue, 2 - yellow*/
		float x;
		float y;
		// 초기 위치 추가될 예정

		GameStart(const int owner)
			: info(sizeof(GameStart), ServerToClient::GAMESTART)
			, owner(owner), color(), x(), y(182.f)
		{}
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
		float z;
		float directionX;
		float directionY;
		float directionZ;

		Move(const int owner, const int type/*ClientToServer::Move, ServerToClient::Move*/)
			: info(sizeof(Move), type)
			, owner(owner), speed(), x(), y(), z(), directionX(), directionY(), directionZ()
		{}
	};
}
#pragma pack(pop)

#endif // !PROTOCOL_H