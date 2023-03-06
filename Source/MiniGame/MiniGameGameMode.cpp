// Copyright Epic Games, Inc. All Rights Reserved.


#include "MiniGameGameMode.h"
#include "MiniGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UIManager.h"
#include "MainUI.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h" // 카메라 헤더
#include "CameraForMinimap.h"
#include "ServerManager.h"


AMiniGameGameMode::AMiniGameGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder< APawn > PlayerPawnBPClass( TEXT( "/Game/ThirdPersonCPP/Blueprints/BP_ThirdPersonCharacter_Default" ) );

	if ( PlayerPawnBPClass.Class != NULL )
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
	bCreateDefaultPawn = false;
	bServerConnect = false;
	

	/*
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
	*/
}

AMiniGameGameMode::~AMiniGameGameMode()
{
}

void AMiniGameGameMode::Tick( float deltaTime )
{
	Super::Tick(deltaTime);

	/*
	UUserWidget* tempMainUI = ( UIManager::GetInstance() ).GetWidget( EUIPathKey::MAIN );

	if ( Cast< UMainUI >(tempMainUI) )
	{
		Cast< UMainUI >( tempMainUI )->UpdateMiniMap( m_CameraActor );
	}
	*/

	
	if( !bCreateDefaultPawn && GetDefaultPawnClassForController(GetWorld()->GetFirstPlayerController()) != nullptr )
	{
		ServerManager::GetInstance().ConnectToServer();
		bCreateDefaultPawn = true;
		bServerConnect = true;
	}

	if (bServerConnect)
	{
		ServerManager::GetInstance().RecvPacket();
	}
}

void AMiniGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UIManager::GetInstance().CreateUI< UMainUI >( GetWorld(), EUIPathKey::MAIN );
}

