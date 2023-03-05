// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


class UUserWidget;
class UMainUI;
class ULogInUI;
class UWorld;


enum EUIPathKey
{
	LOGIN = 0,
	MAIN = 1,
	ENDPATH = 2,
};


class MINIGAME_API UIManager
{
public:

	static UIManager& GetInstance()
	{
		static UIManager instance;
		return instance;
	}


private:
	UIManager();
	~UIManager();

	TMap<int32, FString > m_UIClassPath_Map;
	TMap<int32, std::pair< TSubclassOf< UUserWidget >, UUserWidget* > > m_UI_Map;

public:

	UUserWidget* GetWidget( int32 uiIndex )
	{
		if ( m_UI_Map.Find( uiIndex ) == false )
			return nullptr;

		return m_UI_Map[ uiIndex ].second;
	}


	template< typename T >
	void CreateUI( UWorld* world, int32 uiIndex )
	{
		if ( world == nullptr )
			return;

		if ( m_UI_Map.Find( uiIndex ) == false )
			return;

		m_UI_Map[ uiIndex ].first = ConstructorHelpersInternal::FindOrLoadClass( m_UIClassPath_Map[ uiIndex ], T::StaticClass() );

		if ( m_UI_Map[ uiIndex ].first == nullptr )
			return;

		m_UI_Map[ uiIndex ].second = CreateWidget< UUserWidget >( world, m_UI_Map[ uiIndex ].first );

		if ( Cast< T >( m_UI_Map[ uiIndex ].second ) == nullptr )
			return;

		( Cast< T >( m_UI_Map[ uiIndex ].second ) )->AddToViewport();
	}
};
