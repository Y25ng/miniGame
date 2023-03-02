#pragma once

#include "CoreMinimal.h"

#define SERVERIP "172.28.35.240"
#define SERVERPORT 9000
class ServerManager
{
private:
	FSocket* m_socket;

private:
	static ServerManager& GetInstance()
	{
		static ServerManager instance;
		return instance;
	}
	ServerManager() = default;
	~ServerManager() = default;
public:
	ServerManager(ServerManager const&) = delete;
	ServerManager& operator=(ServerManager const&) = delete;

	ServerManager(ServerManager&&) = delete;
	ServerManager& operator=(ServerManager&&) = delete;

	// Init
	void Initialize();
	void ConnectToServer();

	// ��Ŷ �ۼ��� �Լ�
	void RecvPacket();
	void SendPacket( char datainfo, void* packet );
	void ProcessPacket( char* packet );
};