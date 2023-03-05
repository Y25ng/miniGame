// Fill out your copyright notice in the Description page of Project Settings.


#include "UserManager.h"
#include "MiniGameCharacter.h"
// #include "ServerManager.h"


UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

void UserManager::PushPlayer( int32 key, AMiniGameCharacter* character )
{
	PlayerMap.Add( key, character );
	int32 num = PlayerMap.Num();
}
