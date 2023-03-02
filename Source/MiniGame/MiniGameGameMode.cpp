// Copyright Epic Games, Inc. All Rights Reserved.


#include "MiniGameGameMode.h"
#include "MiniGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MainUI.h"
#include "ServerManager.h"


AMiniGameGameMode::AMiniGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder< APawn > PlayerPawnBPClass( TEXT( "/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter" ) );

	if ( PlayerPawnBPClass.Class != NULL )
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
	if (ServerManager::GetInstance().ConnectToServer() == true)
	{
		UE_LOG(LogTemp, Error, TEXT("Connect Success"));
	}
	
	
	
	static ConstructorHelpers::FClassFinder<UUserWidget> Main_UI(TEXT("/Game/StarterContent/Blueprints/BP_MainUI"));

	if (Main_UI.Succeeded())
	{
		MainUI_WidgetBPClass = Main_UI.Class;
	}

	if (MainUI_WidgetBPClass)
	{
		MainUI_Widget = CreateWidget<UUserWidget>(GetWorld(), MainUI_WidgetBPClass);
	}

	if (MainUI_Widget)
	{
		UMainUI* MainUI_Widget_temp = Cast<UMainUI>(MainUI_Widget);

		if (MainUI_Widget_temp)
		{
			MainUI_Widget_temp->AddToViewport();
		}
	}
}

void AMiniGameGameMode::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	ServerManager::GetInstance().RecvPacket();
}