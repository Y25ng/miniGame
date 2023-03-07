// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


class UUserWidget;
class UMainUI;
class ULogInUI;
class UWorld;


// pair< TSubclassOf< UUserWidget >를 Value로 하는 TMap 컨테이너의 Key로 사용
// Widget BP의 경로 Fstring을 Value로 하는 TMap 컨테이너의 Key로 사용
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

	// enum값을 key, WidgetBlueprint 경로를 Value로 저장
	TMap<int32, FString > m_UIClassPath_Map; 

	// enum값을 key, WidgetBlueprint 클래스와 WidgetBlueprint 포인터 객체를 pair 형태로 value로 저장
	TMap<int32, std::pair< TSubclassOf< UUserWidget >, UUserWidget* > > m_UI_Map;

	// 서버에서 전송해주는 게임 시간(단위: 초)
	int32 m_GameTimeSec;

public:

	// key 값을 통해 원하는 Widget 반환
	UUserWidget* GetWidget( int32 uiIndex );

	void SetGameTimeSec( unsigned char var ) { m_GameTimeSec = static_cast<int>( var ); }
	int32 GetGameTimeSec() { return m_GameTimeSec; }

	// 타입 T와 key값을 통해 원하는 Widget 생성 후 출력
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
