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
}

// PACKET TYPE

// CLIENT
namespace ClientToServer
{
	constexpr int LOGIN_REQUEST = 0;
	constexpr int MOVE = 1;
}
// SERVER
namespace ServerToClient
{
	constexpr int FIRSTINFO = -1;
	constexpr int LOGON_OK = 0;
	constexpr int LOGON_FAILED = 1;
	constexpr int GAMESTART = 2;
	constexpr int MOVE = 3;
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
	struct LoginResult
	{
		PacketInfo info;
		char name[InitPlayer::MAX_NAME];
		int owner;

		// 승률도 추가될 수 잇음
		LoginResult(const int owner, const int type)
			: info(sizeof(LoginResult), type)
			, owner(owner), name()
		{}
	};

	// 미니게임 씬 전환 요청 및 초기화 정보 전송
	struct GameStart
	{
		PacketInfo info;
		int owner; /* 플레이어 구분, 로그인 구현 시 추후 닉네임으로 변경*/
		short color; /* 플레이어 고유 색상 0 - red, 1 - blue, 2 - yellow*/
		// 초기 위치 추가될 예정

		GameStart(const int owner)
			: info(sizeof(GameStart), ServerToClient::GAMESTART)
			, owner(owner), color()
		{}
	};

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

		Move(const int owner, const int type)
			: info(sizeof(Move), type)
			, owner(owner), speed(), x(), y(), z(), directionX(), directionY(), directionZ()
		{}
	};
}
#pragma pack(pop)

#endif // !PROTOCOL_H