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

void UserManager::SetPlayerDefaultInfo( int32 key, float x, float y, float directionX, float directionY, int32 color )
{
	if ( PlayerMap.Find( key ) == nullptr )
		return;

	AMiniGameCharacter* tempCharacter = PlayerMap[ key ];

	tempCharacter->SetColor( color );
	tempCharacter->SetDefaultLocation( x, y );
	tempCharacter->SetOwnerIndex(key);

	FVector tempDirection = FVector( directionX, directionY, tempCharacter->GetActorForwardVector().Z );
	tempCharacter->SetActorRotation( tempDirection.Rotation() );
}

void UserManager::SetPlayerTime( unsigned char time )
{
	if ( PlayerMap.Find( m_MainCharacterKey ) == nullptr )
		return;

	AMiniGameCharacter* tempCharacter = PlayerMap[ m_MainCharacterKey];

	tempCharacter->SetGameTimeSec( static_cast< int >( time ) );
}

int32 UserManager::GetCharacterColor( int32 key )
{
	if ( PlayerMap[ key ] == nullptr )
		return -1;

	return  PlayerMap[ key ]->GetColor();
}


