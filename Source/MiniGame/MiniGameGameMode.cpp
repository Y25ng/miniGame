// Copyright Epic Games, Inc. All Rights Reserved.


#include "MiniGameGameMode.h"
#include "MiniGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MainUI.h"


AMiniGameGameMode::AMiniGameGameMode()
{

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder< APawn > PlayerPawnBPClass( TEXT( "/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter" ) );

	if ( PlayerPawnBPClass.Class != NULL )
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
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
