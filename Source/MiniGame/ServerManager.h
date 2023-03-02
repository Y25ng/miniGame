#pragma once


class ServerManager
{
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
};