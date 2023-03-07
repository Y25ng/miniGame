// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


class UUserWidget;
class UMainUI;
class ULogInUI;
class UWorld;


// pair< TSubclassOf< UUserWidget >�� Value�� �ϴ� TMap �����̳��� Key�� ���
// Widget BP�� ��� Fstring�� Value�� �ϴ� TMap �����̳��� Key�� ���
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

	// enum���� key, WidgetBlueprint ��θ� Value�� ����
	TMap<int32, FString > m_UIClassPath_Map; 

	// enum���� key, WidgetBlueprint Ŭ������ WidgetBlueprint ������ ��ü�� pair ���·� value�� ����
	TMap<int32, std::pair< TSubclassOf< UUserWidget >, UUserWidget* > > m_UI_Map;

	// �������� �������ִ� ���� �ð�(����: ��)
	int32 m_GameTimeSec;

public:

	// key ���� ���� ���ϴ� Widget ��ȯ
	UUserWidget* GetWidget( int32 uiIndex );

	void SetGameTimeSec( unsigned char var ) { m_GameTimeSec = static_cast<int>( var ); }
	int32 GetGameTimeSec() { return m_GameTimeSec; }

	// Ÿ�� T�� key���� ���� ���ϴ� Widget ���� �� ���
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
