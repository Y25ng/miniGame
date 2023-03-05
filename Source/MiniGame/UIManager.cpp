// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "UObject/ConstructorHelpers.h"
#include "MainUI.h"
#include "LogInUI.h"


UIManager::UIManager()
{
	m_UIClassPath_Map.Add( EUIPathKey::LOGIN, FString("/Game/StarterContent/Blueprints/BP_LogInUI") );
	m_UIClassPath_Map.Add( EUIPathKey::MAIN, FString("/Game/StarterContent/Blueprints/BP_MainUI") );

	for ( int i = EUIPathKey::LOGIN; i < EUIPathKey::ENDPATH; ++i )
	{
		TSubclassOf< UUserWidget > UIClass;
		UUserWidget* UIWidget;

		m_UI_Map.Add( i, { UIClass, UIWidget } );
	}
}

UIManager::~UIManager()
{
}

