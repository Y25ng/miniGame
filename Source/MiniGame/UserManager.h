// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"


class AMiniGameCharacter;


class MINIGAME_API UserManager
{
private:
	UserManager();
	~UserManager();

	TMap< int32, AMiniGameCharacter* > PlayerMap;
	int32 m_MainCharacterKey;

public:

	static UserManager& GetInstance()
	{
		static UserManager instance;
		return instance;
	}

	void PushPlayer( int32 key, AMiniGameCharacter* character );
	const TMap< int32, AMiniGameCharacter* >& GetPlayerMap() { return PlayerMap; }

	void SetPlayerDefaultInfo( int32 key, float x, float y, int32 color  );
	void SetMainCharacterIndex( int32 key ) { m_MainCharacterKey = key; }
	int32 GetMainCharacterIndex() { return m_MainCharacterKey; }
};

