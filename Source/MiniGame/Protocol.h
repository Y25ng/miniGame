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
	constexpr int LOGON_OK = 0;
	constexpr int LOGON_FAILED = 1;
	constexpr int GAMESTART = 2;
	constexpr int MOVE = 3;
}

// PACKET DECLARE
#pragma pack(push, 1)
struct PacketInfo
{
	unsigned char	size;
	unsigned short	type;
};
namespace Packet
{
	// �α��� ��û
	struct LoginRequest
	{
		PacketInfo info;
		char name[ InitPlayer::MAX_NAME ];
		char password[ InitPlayer::MAX_PASSWORD ];
	};
	// �α��� ���
	struct LoginResult
	{
		PacketInfo info;
		char name[ InitPlayer::MAX_NAME ];
		// �·��� �߰��� �� ����
	};

	// �̴ϰ��� �� ��ȯ ��û �� �ʱ�ȭ ���� ����
	struct GameStart
	{
		PacketInfo info;
		int owner; /* �÷��̾� ����, �α��� ���� �� ���� �г������� ����*/
		short color; /* �÷��̾� ���� ���� 0 - red, 1 - blue, 2 - yellow*/
		// �ʱ� ��ġ �߰��� ����
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
		float directtionY;
		float directionZ;
	};
}
#pragma pack(pop)

#endif // !PROTOCOL_H