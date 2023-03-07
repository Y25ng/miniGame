// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"


class AMiniGameCharacter;


class MINIGAME_API UserManager
{
private:
	UserManager();
	~UserManager();

	// �������� 3���� �÷��̾�� �ο��ϴ� owner ���� key��, �÷��̾� ��ü�� value������ TMap ���·� �����ϴ� �����̳�
	TMap< int32, AMiniGameCharacter* > PlayerMap;

	// ���� �������� �÷��̾� key��
	int32 m_MainCharacterKey;

public:

	static UserManager& GetInstance()
	{
		static UserManager instance;
		return instance;
	}

	void PushPlayer( int32 key, AMiniGameCharacter* character );
	const TMap< int32, AMiniGameCharacter* >& GetPlayerMap() { return PlayerMap; }


	// 3���� �÷��̾ �������� �� �� �÷��̾��� ó�� ���� ��ġ�� �� �÷��̾ ���� �� ������ �Ҵ�
	void SetPlayerDefaultInfo( int32 key, float x, float y, float directionX, float directionY, int32 color  );
	
	void SetPlayerTime( unsigned char time );

	void SetMainCharacterIndex( int32 key ) { m_MainCharacterKey = key; }
	int32 GetMainCharacterIndex() { return m_MainCharacterKey; }
	int32 GetCharacterColor( int32 key ); 
};

