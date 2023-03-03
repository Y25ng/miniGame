// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "UObject/ConstructorHelpers.h"
#include "MainUI.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
}

void UIManager::CreateMainUI( UWorld* world )
{
	static ConstructorHelpers::FClassFinder< UUserWidget > Main_UI(TEXT("/Game/StarterContent/Blueprints/BP_MainUI"));

	if (Main_UI.Succeeded())
	{
		MainUIClass = Main_UI.Class;
	}

	if ( MainUIClass )
	{
		MainUI = CreateWidget< UUserWidget >( world, MainUIClass );
	}

	if ( MainUI && Cast< UMainUI >(MainUI) )
	{
		( Cast< UMainUI >(MainUI) )->AddToViewport();
	}
}
