// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorManager.h"
#include "ColorBottom.h"


ActorManager::ActorManager() 
{
}

ActorManager::~ActorManager()
{
}

void ActorManager::ChangeBottomColor( int32 color, int32 tileIndex )
{
	if ( m_BottomMap.Find( tileIndex ) == nullptr )
	{
		return;
	}

	m_BottomMap[ tileIndex ]->ChangeColor( color );
}

void ActorManager::PushBottom( int32 key, AColorBottom* bottom )
{
	if ( bottom == nullptr )
	{
		return;
	}

	if ( m_BottomMap.Find( key ) == nullptr )
	{
		m_BottomMap.Add( key, bottom );
	}
}
