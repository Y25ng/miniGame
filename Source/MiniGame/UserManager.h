// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"


class AMiniGameCharacter;


class MINIGAME_API UserManager
{
private:
	UserManager();
	~UserManager();

	// 서버에서 3명의 플레이어에게 부여하는 owner 값을 key값, 플레이어 객체를 value값으로 TMap 형태로 저장하는 컨테이너
	TMap< int32, AMiniGameCharacter* > PlayerMap;

	// 현재 조종중인 플레이어 key값
	int32 m_MainCharacterKey;

public:

	static UserManager& GetInstance()
	{
		static UserManager instance;
		return instance;
	}

	void PushPlayer( int32 key, AMiniGameCharacter* character );
	const TMap< int32, AMiniGameCharacter* >& GetPlayerMap() { return PlayerMap; }


	// 3명의 플레이어가 입장했을 때 각 플레이어의 처음 시작 위치와 각 플레이어가 가질 색 정보를 할당
	void SetPlayerDefaultInfo( int32 key, float x, float y, float directionX, float directionY, int32 color  );
	
	void SetPlayerTime( unsigned char time );

	void SetMainCharacterIndex( int32 key ) { m_MainCharacterKey = key; }
	int32 GetMainCharacterIndex() { return m_MainCharacterKey; }
	int32 GetCharacterColor( int32 key ); 
};

