// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "UObject/ConstructorHelpers.h"
#include "MainUI.h"
#include "LogInUI.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
}

void UIManager::CreateMainUI( UWorld* world )
{
	if ( world == nullptr )
		return;

	FString path = TEXT("/Game/StarterContent/Blueprints/BP_MainUI");
	MainUIClass = ConstructorHelpersInternal::FindOrLoadClass( path, UMainUI::StaticClass());
	
	if (MainUIClass == nullptr )
		return;

	MainUIWidget = CreateWidget< UUserWidget >( world, MainUIClass );
	
	if ( Cast< UMainUI >( MainUIWidget))
	{
		Cast< UMainUI >(MainUIWidget)->CreateMainUI();
	}
}

void UIManager::CreateLogInUI(UWorld* world)
{
	if (world == nullptr)
		return;

	FString path = TEXT("/Game/StarterContent/Blueprints/BP_LogInUI");

	LogInUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, ULogInUI::StaticClass());

	if (LogInUIClass == nullptr)
		return;

	LogInUIWidget = CreateWidget< UUserWidget >(world, LogInUIClass);

	if (Cast< ULogInUI >(LogInUIWidget))
	{
		Cast< ULogInUI >(LogInUIWidget)->CreateLogInUI();
	}
}