// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"


class AColorBottom;
class ALobbyBottom;


class MINIGAME_API ActorManager
{
private:
	ActorManager();
	~ActorManager();

	AColorBottom* m_ColorBottom;
	ALobbyBottom* m_LobbyBottom;
	TMap< int32, AColorBottom* > m_BottomMap;

public:
	static ActorManager& GetInstance()
	{
		static ActorManager instance;
		return instance;
	}

	// 캐릭터가 밟고 있는 바닥을 캐릭터가 할당받은 색깔로 변경해주는 함수
	void ChangeBottomColor( int32 color, int32 tileIndex );

	// 레벨에 배치되어있는 ColorBottom을 TMap으로 관리
	void PushBottom( int32 key, AColorBottom* bottom );

	void SetColorBottom( AColorBottom* var_ColorBottom ) { m_ColorBottom = var_ColorBottom; }
	AColorBottom* GetColorBottom() { return m_ColorBottom; }
	void SetLobbyBottom( ALobbyBottom* var_LobbyBottom ) { m_LobbyBottom = var_LobbyBottom; }
	ALobbyBottom* GetLobbyBottom() { return m_LobbyBottom; }
};
