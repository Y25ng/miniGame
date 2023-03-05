

#pragma once


#include "CoreMinimal.h"
#include "Protocol.h"


// #define SERVERIP "172.28.35.240"
#define SERVERIP "192.168.0.24" // 임시 IP
#define SERVERPORT 9000


class AMiniGameCharacter;


class ServerManager
{
private:
	FSocket* m_socket;
	char m_buf[InitPacket::MAX_BUFFERSIZE];
	unsigned char m_previousPacketSize;
public:
	static ServerManager& GetInstance()
	{
		static ServerManager instance;
		return instance;
	}

private:

	ServerManager();
	~ServerManager();
	
	AMiniGameCharacter* character;
	AMiniGameCharacter* character2;
	AMiniGameCharacter* character3;
	
	bool bGameStart;

public:
	ServerManager(ServerManager const&) = delete;
	ServerManager& operator=(ServerManager const&) = delete;

	ServerManager(ServerManager&&) = delete;
	ServerManager& operator=(ServerManager&&) = delete;

	// Init
	void Initialize();
	bool ConnectToServer();
	void ShutDown();

	// 패킷 송수신 함수
	void RecvPacket();
	void SendPacket( char datainfo, void* packet );
	void ProcessPacket( char* packet );

	
	AMiniGameCharacter* GetCharacter() { return character; }
	void SetCharacter(AMiniGameCharacter* varCharacter) { character = varCharacter; }

	AMiniGameCharacter* GetCharacter2() { return character2; }
	void SetCharacter2(AMiniGameCharacter* varCharacter) { character2 = varCharacter; }

	AMiniGameCharacter* GetCharacter3() { return character3; }
	void SetCharacter3(AMiniGameCharacter* varCharacter) { character3 = varCharacter; }
	
	bool GetbGameStart() { return bGameStart; }
};
