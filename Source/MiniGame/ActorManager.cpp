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
	if ( m_ColorBottom->GetBottomNumber() == tileIndex )
	{
		m_ColorBottom->ChangeColor( color );
	}
}